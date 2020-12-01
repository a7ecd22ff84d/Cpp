#include <stdexcept>
#include <string>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Database/Database.h"
#include "Database/Dataset.h"
#include "Database/Query.h"
#include "Tests/Database/Tools/TestTable.h"

namespace Tests
{
using namespace testing;
using TestTools::TestTableRow;
using TestTools::TestTableRowEq;
using TestTools::TestTableRows;

// I'm using Query both to prepare data and test :)
class QueryTests : public testing::Test
{
public:
	QueryTests() : db(Db::Database("test_files/QueryTests.db"))
	{
		TestTools::dropTestTable(&db);
		TestTools::createTestTable(&db);
	}

	Db::Database db;
};

// error handling
TEST_F(QueryTests, throw_error_on_incorrect_query)
{
	try
	{
		auto sql = "qwer asdf";
		auto query = Db::Query(sql, &db);
		FAIL() << "Logic error about incorrect syntax should be thrown";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = std::string("Db: near \"qwer\": syntax error");

		ASSERT_THAT(err.what(), Eq(expectedMessage));
	}
}

TEST_F(QueryTests, select_test)
{
	TestTools::fillTestTable({{1, 1, "Jeden", 1.1}}, &db);

	auto sql = R"sql(select m.first from test_table m)sql";

	Db::Query query(sql, &db);
	auto dataset = query.execute();

	ASSERT_THAT(dataset.get<int>("first"), Eq(1));
}

TEST_F(QueryTests, parametrs_test)
{
	auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
	query.setParam(":id", 1);
	query.setParam(":first", 1);
	query.setParam(":second", "Jeden");
	query.setParam(":third", 1.1);
	query.executeCommand();

	auto result = TestTools::getTestTabeContent(&db);

	ASSERT_THAT(result.size(), Eq(1));
	ASSERT_THAT(result[0], TestTableRowEq(TestTableRow{1, 1, "Jeden", 1.1}));
}

TEST_F(QueryTests, reusing_query_command_test)
{
	auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
	query.setParam(":id", 1);
	query.setParam(":first", 1);
	query.setParam(":second", "Jeden");
	query.setParam(":third", 1.1);
	query.executeCommand();

	query.setParam(":id", 2);
	query.executeCommand();
}

TEST_F(QueryTests, reusing_query_test)
{
	auto data = TestTableRows{
		{1, 11, "Jeden", 1.1}, {2, 22, "Dwa", 2.2}, {3, 3, "Trzy", 3.3}};
	TestTools::fillTestTable(data, &db);

	auto query = Db::Query(TestTools::getSelectTestTableRowById(), &db);
	query.setParam(":id", 1);
	auto dataset = query.execute();

	// only one row is selected. Last next() resets query so it can be reused
	// immediately
	EXPECT_TRUE(dataset.next());
	EXPECT_THAT(dataset.get<std::string>("second"), Eq("Jeden"));
	EXPECT_FALSE(dataset.next());

	query.setParam(":id", 2);
	dataset = query.execute();
	EXPECT_THAT(dataset.get<std::string>("second"), Eq("Dwa"));

	// query can be also reused after calling query.reset()
	query.reset();
	query.setParam(":id", 3);
	dataset = query.execute();
	EXPECT_THAT(dataset.get<std::string>("second"), Eq("Trzy"));
}

TEST_F(QueryTests, create_dataset_using_temporary_query_object)
{
	auto data = TestTableRow{1, 11, "Jeden", 1.1};
	TestTools::fillTestTable({data}, &db);

	auto dataset =
		Db::Query(TestTools::getSelectTestTableContent(), &db).execute();

	auto result = TestTableRow{
		dataset.get<int>("id"),
		dataset.get<int>("first"),
		dataset.get<std::string>("second"),
		dataset.get<double>("third")};

	EXPECT_THAT(result, TestTableRowEq(data));
}

TEST_F(QueryTests, throw_error_on_incorrect_parameter)
{
	try
	{
		auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
		query.setParam("nonexisting_parameter", "some_value");
		FAIL() << "Logic error about incorrect parameter should be thrown";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = "Db: unknown parameter: 'nonexisting_parameter'";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

TEST_F(QueryTests, throw_error_when_parameter_is_not_set)
{
	try
	{
		auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
		query.executeCommand();

		FAIL() << "Logic error about unset parameter should be thrown";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = "Db: parameter ':first' is not set";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

TEST_F(QueryTests, throw_error_when_execute_command_returns_data)
{
	TestTools::fillTestTable({{1, 1, "Jeden", 1.1}}, &db);

	try
	{
		auto query = Db::Query(TestTools::getSelectTestTableContent(), &db);
		query.executeCommand();

		FAIL() << "Expected logic error";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = "Db: Query returned a value while executing command";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

TEST_F(QueryTests, throw_error_when_query_returns_constraint_violation)
{
	TestTools::fillTestTable({{1, 1, "Jeden", 1.1}}, &db);
	try
	{
		auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
		query.setParam(":id", 1); // this id already exists in database
		query.setParam(":first", 22);
		query.setParam(":second", "dwa");
		query.setParam(":third", 2.2);
		query.executeCommand();

		FAIL() << "Expected logic error";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = "Db: UNIQUE constraint failed: test_table.id";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

TEST_F(QueryTests, throw_error_when_parameter_is_set_without_resetting_statement)
{
	TestTools::fillTestTable({{1, 11, "Jeden", 1.1}}, &db);

	auto query = Db::Query(TestTools::getSelectTestTableRowById(), &db);
	query.setParam(":id", 1);
	auto result = query.execute();

	try
	{
		// a reset should be called here to allow to set new param value
		query.setParam(":id", 2);
		FAIL() << "Expected logic error";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = "Db: bad parameter or other API misuse";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

} // namespace Tests
