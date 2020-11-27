#include "Tests/Database/Tools/TestTable.h"

#include <sstream>

#include "Database/Query.h"

namespace TestTools
{
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
	for (auto rowData : data)
	{
		std::stringstream insertSql;

		// clang-format off
		insertSql <<
			"\n insert into test_table"
			"\n ("
			"\n     id,"
			"\n     first,"
			"\n     second,"
			"\n     third"
			"\n )"
			"\n values "
			"\n ("
			"\n     " << rowData.id << ","
			"\n     " << rowData.first << ","
			"\n     '" << rowData.second << "',"
			"\n     '" << rowData.third << "'"
			"\n )"
		;
		// clang-format on

		Db::Query(insertSql.str(), db).executeCommand();
	}
}

TestTableRows getTestTabeContent(Db::Database* db)
{
	TestTableRows result;
	// todo

	return result;
}

} // namespace TestTools
