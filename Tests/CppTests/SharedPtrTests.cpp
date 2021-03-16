#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Tests
{
using namespace testing;

TEST(SharedPtrTests, swap_test)
{
	using Pointer = std::shared_ptr<int>;

	Pointer i1_p1 = std::make_shared<int>(100);
	Pointer i1_p2 = i1_p1;

	ASSERT_THAT(*i1_p2, Eq(100));

	Pointer i2_p1 = std::make_shared<int>(200);
	Pointer i2_p2 = i2_p1;

	ASSERT_THAT(*i2_p2, Eq(200));

	i2_p2.swap(i1_p2);

	// EXPECT_THAT(*i1_p1, Eq(200)); :(
	EXPECT_THAT(*i1_p2, Eq(200));
	// EXPECT_THAT(*i2_p1, Eq(100)); :(
	EXPECT_THAT(*i2_p2, Eq(100));
}

TEST(SharedPtrTests, replace_pointer_content_test)
{
	using Pointer = std::shared_ptr<int>;

	Pointer i1_p1 = std::make_shared<int>(100);
	Pointer i1_p2 = i1_p1;

	ASSERT_THAT(*i1_p2, Eq(100));

	Pointer i2_p1 = std::make_shared<int>(200);
	Pointer i2_p2 = i2_p1;

	ASSERT_THAT(*i2_p2, Eq(200));

	*i1_p2 = *i2_p2;

	EXPECT_THAT(*i1_p1, Eq(200));
	EXPECT_THAT(*i1_p2, Eq(200));
}

} // namespace Tests