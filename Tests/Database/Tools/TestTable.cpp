#include "Tests/Database/Tools/TestTable.h"

#include <sstream>

#include "Database/Query.h"

namespace TestTools
{
testing::Matcher<TestTableRow> TestTableRowEq(const TestTableRow& expected)
{
	return AllOf(
		testing::Field("id", &TestTableRow::id, expected.id),
		testing::Field("first", &TestTableRow::first, expected.first),
		testing::Field("second", &TestTableRow::second, expected.second),
		testing::Field("third", &TestTableRow::third, expected.third));
}

std::string getInsertUsingParametersSql()
{
	return R"sql(
		insert into test_table
		(
		    id,
		    first,
		    second,
		    third
		)
		values 
		(
		 	:id,
			:first,
			:second,
			:third
		)
		)sql";
}

std::string getSelectTestTableContent()
{
	return R"sql(
		select
			id,
			first,
			second,
			third
		from
			test_table
		order by
			id
		)sql";
}

void dropTestTable(Db::Database* db)
{
	auto sql = R"sql(drop table if exists test_table)sql";
	Db::Query(sql, db).executeCommand();
}

void createTestTable(Db::Database* db)
{
	auto createTableSql = R"sql(
		create table test_table(
			id int primary key not null,
			first int,
			second char(20),
			third double)
		)sql";

	Db::Query(createTableSql, db).executeCommand();
}

void fillTestTable(TestTableRows data, Db::Database* db)
{
	auto query = Db::Query(getInsertUsingParametersSql(), db);

	for (auto rowData : data)
	{
		query.setParam(":id", rowData.id);
		query.setParam(":first", rowData.first);
		query.setParam(":second", rowData.second);
		query.setParam(":third", rowData.third);
		query.executeCommand();
	}
}

TestTableRows getTestTabeContent(Db::Database* db)
{
	TestTableRows result;

	auto query = Db::Query(getSelectTestTableContent(), db);
	auto dataset = query.execute();

	result.emplace_back(TestTableRow{
		dataset.get<int>("id"),
		dataset.get<int>("first"),
		dataset.get<std::string>("second"),
		dataset.get<double>("third")});

	return result;
}

} // namespace TestTools
