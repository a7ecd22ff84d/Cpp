
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Database/Database.h"
#include "Database/Query.h"
#include "Tests/Database/Tools/TestTable.h"

namespace Tests
{
using namespace testing;
using TestTools::getSelectTestTableContent;

class ValueGetterTests : public testing::Test
{
public:
	ValueGetterTests() : db(Db::Database("test_files/ValueGetterTests.db"))
	{
		TestTools::dropTestTable(&db);
		TestTools::createTestTable(&db);
	}

	Db::Database db;
};

// Getting value of simple types is already tested in query and dataset tests

TEST_F(ValueGetterTests, throw_error_when_cannot_cast_to_required_type)
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

TEST_F(ValueGetterTests, throw_error_when_value_is_empty)
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

} // namespace Tests
