#include <type_traits>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Database/Database.h"

namespace Tests
{
TEST(DatabaseTest, database_is_not_copyable)
{
	// It is not exactly test, Database class cannot be copied, otherwise,
	// because when temporary copy is deleted database is disconnected.

	EXPECT_FALSE(std::is_copy_assignable_v<Db::Database>);
	EXPECT_FALSE(std::is_copy_constructible_v<Db::Database>);
}

} // namespace Tests