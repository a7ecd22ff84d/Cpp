#include <vector>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Core/Containers/LoopIterator.h>

namespace Tests
{
using namespace testing;

TEST(LoopIteratorTests, point_to_beginning_when_created)
{
	auto v = std::vector<int>{1,2,3,4};
	Containers::LoopIterator lit(v);

	EXPECT_THAT(*lit, Eq(1));
}

TEST(LoopIteratorTests, iterate_in_both_ways)
{
	auto v = std::vector<int>{1,2,3,4};
	Containers::LoopIterator lit(v);
	
	lit++;
	EXPECT_THAT(*lit, Eq(2));

	lit+=2;
	EXPECT_THAT(*lit, Eq(4));

	lit--;
	EXPECT_THAT(*lit, Eq(3));

	lit-=2;
	EXPECT_THAT(*lit, Eq(1));
}

TEST(LoopIteratorTests, returns_to_begin_when_reached_end_od_a_container)
{
	auto v = std::vector<int>{1,2,3,4};
	Containers::LoopIterator lit(v);
	
	lit+=3; // go to the end of a vector
	lit++;
	EXPECT_THAT(*lit, Eq(1));

	lit+=5;
	EXPECT_THAT(*lit, Eq(2));
}

TEST(LoopIteratorTests, returns_to_end_when_reached_begin_od_a_container)
{
	auto v = std::vector<int>{1,2,3,4};
	Containers::LoopIterator lit(v);
	
	lit--;
	EXPECT_THAT(*lit, Eq(4));

	lit-=5;
	EXPECT_THAT(*lit, Eq(3));
}

TEST(LoopIteratorTests, set_item_value_by_iterator)
{
	auto v = std::vector<int>{1,2,3,4};
	Containers::LoopIterator lit(v);
	
	*lit = 11;

	EXPECT_THAT(v[0], Eq(11));
}

} // namespace Tests
