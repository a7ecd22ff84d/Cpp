#include <gtest/gtest.h>

#include "Core/Containers/EnumMapper.hpp"

namespace Tests
{
using namespace testing;

enum class TestEnum
{
	Red,
	Blue,
	Green
};

TEST(EnumMapperTests, enum_mapper_test)
{
	constexpr auto mapper =
		Containers::EnumMapper<TestEnum, 3, 5>{Containers::EnumData<TestEnum, 3>{
			{{TestEnum::Red, "Red"},
			 {TestEnum::Blue, "Blue"},
			 {TestEnum::Green, "Green"}}}};

	{
		constexpr auto strValue = mapper.toString(TestEnum::Red);
		static_assert(strValue, "Red");
		EXPECT_EQ(strValue, "Red");
	}
	{
		constexpr auto strValue = mapper.toString(TestEnum::Blue);
		static_assert(strValue, "Blue");
		EXPECT_EQ(strValue, "Blue");
	}
	{
		constexpr auto strValue = mapper.toString(TestEnum::Green);
		static_assert(strValue, "Green");
		EXPECT_EQ(strValue, "Green");
	}

	{
		constexpr auto enumValue = mapper.toEnum("Red");
		static_assert(enumValue == TestEnum::Red);
		EXPECT_EQ(enumValue, TestEnum::Red);
	}
	{
		constexpr auto enumValue = mapper.toEnum("Blue");
		static_assert(enumValue == TestEnum::Blue);
		EXPECT_EQ(enumValue, TestEnum::Blue);
	}
	{
		constexpr auto enumValue = mapper.toEnum("Green");
		static_assert(enumValue == TestEnum::Green);
		EXPECT_EQ(enumValue, TestEnum::Green);
	}
} // namespace Tests

// TEST(TwoWayStaticMapTests, fail_to_build_when_passing_nonexisting_value)
// {
// 	constexpr auto mapper =
// 		Containers::EnumMapper<TestEnum, 2, 5>{Containers::EnumData<TestEnum, 2>{
// 			{{TestEnum::Red, "Red"}, {TestEnum::Blue, "Blue"}}}};

// 	// constexpr mapper.toEnum("Red2");
// }

// TEST(TwoWayStaticMapTests, fail_to_build_when_passing_nonregistered_enum)
// {
// 	constexpr auto mapper =
// 		Containers::EnumMapper<TestEnum, 2, 5>{Containers::EnumData<TestEnum, 2>{
// 			{{TestEnum::Red, "Red"}, {TestEnum::Blue, "Blue"}}}};

// 	constexpr auto enumValue =  mapper.toString(TestEnum::Green);
// }

} // namespace Tests
