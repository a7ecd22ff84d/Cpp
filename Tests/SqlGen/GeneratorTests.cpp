#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "SqlGen/Generator.h"

namespace Tests
{
using namespace testing;

TEST(GeneratorTests, register_tables_and_get_table_list)
{
	auto generator = SqlGen::Generator();
	ASSERT_THAT(generator.getRegisteredTables().size(), Eq(0));

	generator.registerTable(R"yaml(name: test_table)yaml");
	ASSERT_THAT(generator.getRegisteredTables(), ElementsAre("test_table"));

	generator.registerTable(R"yaml(name: test_table2)yaml");
	ASSERT_THAT(
		generator.getRegisteredTables(), ElementsAre("test_table", "test_table2"));
}

class CreateTests : public testing::Test
{
public:
	SqlGen::Generator generator;

	void runTest(const char* yamlDefinition, const char* expectedSqlStatement)
	{
		generator.registerTable(yamlDefinition);
		auto result = generator.getCreateStatement("test_table");
		ASSERT_STREQ(result.c_str(), expectedSqlStatement);
	}
};

TEST_F(CreateTests, get_simple_create_table_query)
{
	auto definition = R"yaml(
name: test_table
fields:
  - name: id
    type: int
  - name: first
    type: int
  - name: second
    type: text
)yaml";

	auto expected = R"sql(
CREATE TABLE test_table
(
	id int,
	first int,
	second text
)
)sql";

	runTest(definition, expected);
}

TEST_F(CreateTests, constraints_test)
{
	auto definition = R"yaml(
name: test_table
fields:
  - name: id
    type: int
    constraint: PRIMARY KEY
  - name: first
    type: int
    constraint: FOREIGN KEY(other_table.id)
  - name: second
    type: text
    constraint: UNIQUE NOT NULL
)yaml";

	auto expected = R"sql(
CREATE TABLE test_table
(
	id int PRIMARY KEY,
	first int FOREIGN KEY(other_table.id),
	second text UNIQUE NOT NULL
)
)sql";

	runTest(definition, expected);
}

} // namespace Tests
