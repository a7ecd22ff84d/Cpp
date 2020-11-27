#include <stdexcept>
#include <vector>

#include <gmock/gmock.h>

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

// TEST_F(QueryTests, select_test)
// {
// 	fillMainTable({{1, 1, "Jeden", 1.1}});

// 	auto sql = R"sql(select m.first from main_table m)sql";

// 	Db::Query query(sql, &db);
// 	auto dataset = query.execute();

// 	ASSERT_THAT(dataset.get<int>("first"), Eq(1));
// }

} // namespace Tests
