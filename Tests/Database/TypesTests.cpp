
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Database/Database.h"
#include "Database/Query.h"
#include "Tests/Database/Tools/TestTable.h"

namespace Tests
{
using namespace testing;
using TestTools::getSelectTestTableContent;

class TypesTests : public testing::Test
{
public:
	TypesTests() : db(Db::Database("test_files/TypesTests.db"))
	{
		TestTools::dropTestTable(&db);
		TestTools::createTestTable(&db);
	}

	Db::Database db;
};

// Getting and serring value of simple types is already tested
// in query and dataset tests

class SimpleTypesTests : public TypesTests
{
};

TEST_F(SimpleTypesTests, throw_error_when_cannot_cast_to_required_type)
{
	TestTools::fillTestTable({{1, 1, "Jeden", 1.1}}, &db);
	auto dataset = Db::Query(getSelectTestTableContent(), &db).execute();

	try
	{
		dataset.get<int>("second");
		FAIL() << "Expected logic error";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage =
			"Db: Cannot cast value 'Jeden' of column 'second' to 'int'";
		ASSERT_STREQ(err.what(), expectedMessage);
	}

	try
	{
		dataset.get<double>("second");
		FAIL() << "Expected logic error";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage =
			"Db: Cannot cast value 'Jeden' of column 'second' to 'double'";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

TEST_F(SimpleTypesTests, throw_error_when_value_is_empty)
{
	TestTools::fillTestTable({{1, 1, "", 1.1}}, &db);
	auto dataset = Db::Query(getSelectTestTableContent(), &db).execute();

	try
	{
		dataset.get<int>("second");
		FAIL() << "Expected logic error";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage =
			"Db: Cannot cast empty value of column 'second' to 'int'";
		ASSERT_STREQ(err.what(), expectedMessage);
	}

	try
	{
		dataset.get<double>("second");
		FAIL() << "Expected logic error";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage =
			"Db: Cannot cast empty value of column 'second' to 'double'";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

class OptionalTypesTests : public TypesTests
{
};

TEST_F(OptionalTypesTests, insert_and_select_null_when_optional_is_not_initialized)
{
	auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
	query.setParam(":id", 1);
	query.setParam(":first", std::optional<int>());
	query.setParam(":second", "Tests");
	query.setParam(":third", 1.1);
	query.executeCommand();

	auto dataset = Db::Query(getSelectTestTableContent(), &db).execute();
	ASSERT_FALSE(dataset.get<std::optional<int>>("first").has_value());
}

TEST_F(OptionalTypesTests, insert_and_select_null_when_nullopt_is_used)
{
	auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
	query.setParam(":id", 1);
	query.setParam(":first", std::nullopt);
	query.setParam(":second", "Tests");
	query.setParam(":third", 1.1);
	query.executeCommand();

	auto dataset = Db::Query(getSelectTestTableContent(), &db).execute();
	ASSERT_FALSE(dataset.get<std::optional<int>>("first").has_value());
}

TEST_F(OptionalTypesTests, insert_and_select_value_when_optional_is_initialized)
{
	auto query = Db::Query(TestTools::getInsertUsingParametersSql(), &db);
	query.setParam(":id", 1);
	query.setParam(":first", std::optional<int>(10));
	query.setParam(":second", "Tests");
	query.setParam(":third", 1.1);
	query.executeCommand();

	auto dataset = Db::Query(getSelectTestTableContent(), &db).execute();
	EXPECT_THAT(dataset.get<int>("first"), Eq(10));
	EXPECT_THAT(*dataset.get<std::optional<int>>("first"), Eq(10));
}

} // namespace Tests
