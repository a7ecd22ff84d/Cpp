#include <stdexcept>
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
	ASSERT_THAT(
		result[0], TestTableRowEq(TestTools::TestTableRow{1, 1, "Jeden", 1.1}));
}

TEST_F(QueryTests, allow_to_set_paramer_multiple_times)
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

} // namespace Tests
