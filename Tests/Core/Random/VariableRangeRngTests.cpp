#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Core/Random/VariableRangeRng.h"

namespace Tests
{
using namespace testing;

TEST(VariableRangeRngTests, generate_number_from_range)
{
	VariableRangeRng rng;

	EXPECT_THAT(rng.getRandom(1, 10), AllOf(Ge(1), Le(10)));
}

TEST(VariableRangeRngTests, generate_random_numbers)
{
	VariableRangeRng rng;

	auto v = std::vector<int>(1000);
	std::generate(v.begin(), v.end(), [&rng]() { return rng.getRandom(1, 100); });

	EXPECT_TRUE(std::any_of(v.begin(), v.end(), [&v](int x) { return x != v[0]; }));
}

TEST(VariableRangeRngTests, generate_numbers_from_different_ranges)
{
	VariableRangeRng rng;

	EXPECT_THAT(rng.getRandom(1, 10), AllOf(Ge(1), Le(10)));
	EXPECT_THAT(rng.getRandom(10, 20), AllOf(Ge(10), Le(20)));
	EXPECT_THAT(rng.getRandom(20, 30), AllOf(Ge(20), Le(30)));
	EXPECT_THAT(rng.getRandom(30, 40), AllOf(Ge(30), Le(40)));
	EXPECT_THAT(rng.getRandom(40, 50), AllOf(Ge(40), Le(50)));
}

TEST(VariableRangeRngTests, use_seed_to_generate_numbers)
{
	VariableRangeRng rng1("random_seed");
	VariableRangeRng rng2("random_seed");

	for (auto i = 0; i < 1000; i++)
		EXPECT_THAT(rng1.getRandom(1, 100), Eq(rng2.getRandom(1, 100)));
}

TEST(VariableRangeRngTests, do_not_use_seed_when_it_is_empty)
{
	VariableRangeRng rng1(""); // default constructor
	VariableRangeRng rng2("");

	auto difference{false};
	for (auto i = 0; i < 1000; i++ || difference)
		difference = rng1.getRandom(1, 100) != rng2.getRandom(1, 100);

	EXPECT_TRUE(difference);
}

} // namespace Tests
