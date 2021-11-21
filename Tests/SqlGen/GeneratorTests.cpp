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

	generator.registerTable(R"json({"name": "test_table"})json");
	ASSERT_THAT(generator.getRegisteredTables(), ElementsAre("test_table"));

	generator.registerTable(R"json({"name": "test_table2"})json");
	ASSERT_THAT(
		generator.getRegisteredTables(), ElementsAre("test_table", "test_table2"));
}

} // namespace Tests
