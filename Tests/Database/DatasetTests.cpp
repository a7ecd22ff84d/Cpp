#include <string>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Database/Database.h"
#include "Database/Query.h"
#include "Tests/Database/Tools/TestTable.h"

namespace Tests
{
using namespace testing;

class DatasetTests : public testing::Test
{
public:
	DatasetTests() : db(Db::Database("test_files/DatasetTests.db"))
	{
		TestTools::dropTestTable(&db);
		TestTools::createTestTable(&db);
	}

	Db::Database db;
};

TEST_F(DatasetTests, empty_dataset_test)
{
	auto query = Db::Query(TestTools::getSelectTestTableContent(), &db);
	auto dataset = query.execute();

	ASSERT_TRUE(dataset.empty());

	TestTools::fillTestTable({{1, 11, "Jeden", 1.1}}, &db);
	dataset = query.execute();

	ASSERT_FALSE(dataset.empty());
}

TEST_F(DatasetTests, select_simple_values_test)
{
	TestTools::fillTestTable({{1, 11, "Jeden", 1.1}}, &db);

	auto query = Db::Query(TestTools::getSelectTestTableContent(), &db);
	auto dataset = query.execute();

	EXPECT_THAT(dataset.get<int>("id"), Eq(1));
	EXPECT_THAT(dataset.get<int>("first"), Eq(11));
	EXPECT_THAT(dataset.get<std::string>("second"), Eq("Jeden"));
	EXPECT_THAT(dataset.get<double>("third"), Eq(1.1));
}

TEST_F(DatasetTests, select_multiple_rows_test)
{
	auto data = TestTools::TestTableRows{
		{1, 11, "Jeden", 1.1}, {2, 22, "Dwa", 2.2}, {3, 3, "Trzy", 3.3}};

	TestTools::fillTestTable(data, &db);

	auto query = Db::Query(TestTools::getSelectTestTableContent(), &db);
	auto dataset = query.execute();

	auto rowId = 0u;
	while (dataset.next())
	{
		EXPECT_THAT(dataset.get<int>("id"), Eq(data[rowId].id));
		EXPECT_THAT(dataset.get<int>("first"), Eq(data[rowId].first));
		EXPECT_THAT(dataset.get<std::string>("second"), Eq(data[rowId].second));
		EXPECT_THAT(dataset.get<double>("third"), Eq(data[rowId].third));

		if (++rowId > data.size())
			FAIL() << "Inifinite loop";
	}

	ASSERT_THAT(rowId, Eq(data.size()));
}

TEST_F(DatasetTests, next_returns_false_when_dataset_is_empty)
{
	auto query = Db::Query(TestTools::getSelectTestTableContent(), &db);
	auto dataset = query.execute();

	ASSERT_FALSE(dataset.next());
}

TEST_F(DatasetTests, throw_error_on_incorrect_column_name)
{
	TestTools::fillTestTable({{1, 11, "Jeden", 1.1}}, &db);

	auto query = Db::Query(TestTools::getSelectTestTableContent(), &db);
	auto dataset = query.execute();

	try
	{
		dataset.get<int>("nonexistent_column");

		FAIL() << "Logic error about nonexistent column should be thrown";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = "Db: column 'nonexistent_column' does not exist";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

TEST_F(DatasetTests, throw_error_when_getting_value_from_empty_dataset)
{
	auto query = Db::Query(TestTools::getSelectTestTableContent(), &db);
	auto dataset = query.execute();

	try
	{
		dataset.get<int>("id");

		FAIL() << "Expected logic error about empty dataset";
	}
	catch (std::logic_error& err)
	{
		auto expectedMessage = "Db: dataset is empty";
		ASSERT_STREQ(err.what(), expectedMessage);
	}
}

} // namespace Tests
