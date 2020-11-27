#include <gmock/gmock.h>

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

TEST_F(DatasetTests, select_simple_values_test)
{
	TestTools::fillTestTable({{1, 11, "Jeden", 1.1}}, &db);

	auto sql = R"sql(
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

	auto query = Db::Query(sql, &db);
	auto dataset = query.execute();

	EXPECT_THAT(dataset.get<int>("id"), Eq(1));
	EXPECT_THAT(dataset.get<int>("first"), Eq(11));
	EXPECT_THAT(dataset.get<std::string>("second"), Eq("Jeden"));
	EXPECT_THAT(dataset.get<double>("third"), Eq(1.1));
}

} // namespace Tests
