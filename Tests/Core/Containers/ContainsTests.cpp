#include <vector>

#include <Core/Containers/Contains.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Tests
{
using namespace testing;

TEST(ContainsTests, vector_test)
{
	auto v = std::vector<int>{1, 2, 3, 4};

	ASSERT_TRUE(Containers::contains(v, 1));
	ASSERT_FALSE(Containers::contains(v, 10));
}

TEST(ContainsTests, initializer_list_test)
{
	auto v = {1, 2, 3, 4};

	ASSERT_TRUE(Containers::contains(v, 1));
}

// TEST(ContainsTests, map_test)
// {
// 	auto v = std::map<int, std::string>{{1, "first"}, {2, "second"}};

// 	ASSERT_TRUE(Containers::contains(v, 1));
// }

} // namespace Tests
