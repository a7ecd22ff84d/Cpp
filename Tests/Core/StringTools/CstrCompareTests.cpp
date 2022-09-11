#include <gtest/gtest.h>

#include "Core/StringTools/CstrCompare.hpp"

namespace Tests
{

TEST(CstrCompareTests, compare_cstr)
{
	static_assert(!StringTools::cstrCompare("aaa", "bbb"));
	static_assert(!StringTools::cstrCompare("abcd", "abc"));
	static_assert(!StringTools::cstrCompare("abc", "abcd"));
	static_assert(!StringTools::cstrCompare("", "a"));
	static_assert(!StringTools::cstrCompare("a", ""));
	static_assert(StringTools::cstrCompare("abc", "abc"));

	EXPECT_FALSE(StringTools::cstrCompare("aaa", "bbb"));
	EXPECT_FALSE(StringTools::cstrCompare("abcd", "abc"));
	EXPECT_FALSE(StringTools::cstrCompare("abc", "abcd"));
	EXPECT_FALSE(StringTools::cstrCompare("", "a"));
	EXPECT_FALSE(StringTools::cstrCompare("a", ""));
	EXPECT_TRUE(StringTools::cstrCompare("abc", "abc"));
}

} // namespace Tests