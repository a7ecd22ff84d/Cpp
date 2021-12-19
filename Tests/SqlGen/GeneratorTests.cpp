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

class QueryTests : public testing::Test
{
public:
	SqlGen::Generator generator;

	QueryTests()
	{
		const auto sampleDefintion = R"yaml(
name: test_table
fields:
  - name: id
    type: int
    constraint: PRIMARY KEY
  - name: int_field
    type: int
    constraint: NOT NULL
  - name: text_field
    type: text
  - name: date_field
    type: date
)yaml";

		generator.registerTable(sampleDefintion);
	}
};

TEST_F(QueryTests, select_tests)
{
	auto expected = R"sql(
SELECT
(
	id,
	int_field,
	text_field,
	date_field
)
FROM test_table
)sql";

	auto result = generator.getSelectStatement("test_table");
	ASSERT_STREQ(result.c_str(), expected);
}

TEST_F(QueryTests, insert_tests)
{
	auto expected = R"sql(
INSERT INTO test_table
(
	id,
	int_field,
	text_field,
	date_field
)
VALUES
(
	:id,
	:int_field,
	:text_field,
	:date_field
)
)sql";

	auto result = generator.getInsertStatement("test_table");
	ASSERT_STREQ(result.c_str(), expected);
}

TEST_F(QueryTests, update_tests)
{
	auto expected = R"sql(
UPDATE test_table
SET
	int_field = :int_field,
	text_field = :text_field,
	date_field = :date_field
WHERE
	id = :id
)sql";

	auto result = generator.getUpdateStatement("test_table");
	ASSERT_STREQ(result.c_str(), expected);
}

} // namespace Tests
