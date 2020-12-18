#include <gmock/gmock.h>

#include <Core/Types/IsOptional.h>

namespace Tests
{
using namespace testing;

TEST(IsOptionalTests, returns_false_when_variable_is_not_optional)
{
	EXPECT_FALSE(::Types::isOptional_v<int>);
}

TEST(IsOptionalTests, returns_true_when_variable_is_optional)
{
	auto opt = std::make_optional<double>(22.12);
	EXPECT_TRUE(::Types::isOptional_v<decltype(opt)>);
}

TEST(IsOptionalTests, returns_true_when_variable_is_unitialized_optional)
{
	auto opt = std::make_optional<double>();
	EXPECT_TRUE(::Types::isOptional_v<decltype(opt)>);
}

TEST(IsOptionalTests, returns_true_when_variable_is_nullopt)
{
	EXPECT_FALSE(::Types::isOptional_v<std::nullopt_t>);
}

} // namespace Tests
