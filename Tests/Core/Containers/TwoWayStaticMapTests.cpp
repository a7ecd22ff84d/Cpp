#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Core/Containers/TwoWayStaticMap.hpp"

namespace Tests
{
using namespace testing;

enum class TestEnum
{
	Red,
	Blue
};

TEST(TwoWayStaticMapTests, compare_cstr)
{
	static_assert(!Containers::compareCstr("aaa", "bbb"));
	static_assert(!Containers::compareCstr("abcd", "abc"));
	static_assert(!Containers::compareCstr("abc", "abcd"));
	static_assert(!Containers::compareCstr("", "a"));
	static_assert(!Containers::compareCstr("a", ""));
	static_assert(Containers::compareCstr("abc", "abc"));

	EXPECT_FALSE(Containers::compareCstr("aaa", "bbb"));
	EXPECT_FALSE(Containers::compareCstr("abcd", "abc"));
	EXPECT_FALSE(Containers::compareCstr("abc", "abcd"));
	EXPECT_FALSE(Containers::compareCstr("", "a"));
	EXPECT_FALSE(Containers::compareCstr("a", ""));
	EXPECT_TRUE(Containers::compareCstr("abc", "abc"));
} // namespace Tests

TEST(TwoWayStaticMapTests, enum_mapper_test)
{
	constexpr auto mapper =
		Containers::EnumMapper<TestEnum, 2, 5>{Containers::EnumData<TestEnum, 2>{
			{{TestEnum::Red, "Red"}, {TestEnum::Blue, "Blue"}}}};

	constexpr auto strValue = mapper.toSv(TestEnum::Red);
	static_assert(strValue, "Red");
	EXPECT_EQ(strValue, "Red");

	constexpr auto enumValue = mapper.toEnum("Red");
	static_assert(enumValue == TestEnum::Red);
	EXPECT_EQ(enumValue, TestEnum::Red);
} // namespace Tests

// TEST(TwoWayStaticMapTests, fail_to_build_when_passing_nonexisting_value)
// {
// 	constexpr auto mapper =
// 		Containers::EnumMapper<TestEnum, 2, 5>{Containers::EnumData<TestEnum, 2>{
// 			{{TestEnum::Red, "Red"}, {TestEnum::Blue, "Blue"}}}};

// 	constexpr auto enumValue = mapper.toEnum("Red2");
// 	static_assert(enumValue == TestEnum::Red);
// 	EXPECT_EQ(enumValue, TestEnum::Red);
// } // namespace Tests

} // namespace Tests
