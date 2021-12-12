
#include <date/date.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Core/Date/DateSqlParam.h"
#include "Database/Database.h"
#include "Database/Query.h"

namespace Tests
{
using namespace date;
using namespace testing;

class DateTypeTests : public testing::Test
{
public:
	DateTypeTests() : db(Db::Database("test_files/DateTypeTests.db"))
	{
		auto dropSql = R"sql(DROP TABLE test_table)sql";

		auto sql = R"sql(
CREATE TABLE test_table
(
	id INT PRIMARY KEY,
	date_column DATE
))sql";

		Db::Query(dropSql, &db).executeCommand();
		Db::Query(sql, &db).executeCommand();
	}

	Db::Database db;
};

TEST_F(DateTypeTests, set_date_param_and_get_as_string)
{
	auto date{2019_y / date::September / 20};
	auto expected = "2019-09-20";

	auto insertSql = R"sql(
		INSERT INTO test_table (id, date_column)
		VALUES (:id, :date_column))sql";

	auto selectSql =
		R"sql(SELECT tt.date_column FROM test_table tt WHERE tt.id = :id)sql";

	auto insertQuery = Db::Query(insertSql, &db);
	insertQuery.setParam(":id", 1);
	insertQuery.setParam(":date_column", date);
	insertQuery.executeCommand();

	auto selectQuery = Db::Query(selectSql, &db);
	selectQuery.setParam(":id", 1);

	auto result = selectQuery.execute().get<std::string>("date_column");
	ASSERT_THAT(result, Eq(expected));
}

TEST_F(DateTypeTests, set_as_string_and_get_as_date)
{
	auto dateStr = "2019-09-20";
	auto expected{2019_y / date::September / 20};

	auto insertSql = R"sql(
		INSERT INTO test_table (id, date_column)
		VALUES (:id, :date_column))sql";

	auto selectSql =
		R"sql(SELECT tt.date_column FROM test_table tt WHERE tt.id = :id)sql";

	auto insertQuery = Db::Query(insertSql, &db);
	insertQuery.setParam(":id", 1);
	insertQuery.setParam(":date_column", dateStr);
	insertQuery.executeCommand();

	auto selectQuery = Db::Query(selectSql, &db);
	selectQuery.setParam(":id", 1);

	auto result = selectQuery.execute().get<date::year_month_day>("date_column");
	ASSERT_THAT(result, Eq(expected));
}


} // namespace Tests
