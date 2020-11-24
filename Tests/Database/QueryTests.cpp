#include <stdexcept>
#include <gmock/gmock.h>

#include "Database/Database.h"
#include "Database/Query.h"

namespace Tests
{
using namespace testing;

// I'm using Query both to prepare data and test :)
class QueryTests : public testing::Test
{
public:
	QueryTests() : db(Db::Database("test_files/QueryTests.db"))
	{
		dropMainTable();
		createMainTable();
	}

	void dropMainTable()
	{
		auto sql = "drop table if exists main";
		Db::Query(sql, &db).executeCommand();
	}

	void createMainTable()
	{
		auto createTableSql = R"sql(
			create table main(
			    id int primary key not null,
			    first int,
			    second char(20),
			    third double)
			)sql";

		Db::Query(createTableSql, &db).executeCommand();
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
		auto expectedMessage =
			std::string("Db: near \"qwer\": syntax error");

		ASSERT_THAT(err.what(), Eq(expectedMessage));
	}
}

// TEST_F(QueryTests, execute_command_test)
// {
// }

} // namespace Tests
