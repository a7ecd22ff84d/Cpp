#include <algorithm>
#include <cctype>
#include <string_view>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// do sprawdzenia:

// while + isDigit
// try catch
// regex
// find_first_not_of
// find_if
// std::all_of

namespace Tests
{
using namespace testing;

///////////////////////////////////////////////////////////////////////////////

bool isNumber_find_if_not_lambda(std::string_view text)
{
	auto isDigit = [](char c) -> bool { return std::isdigit(c); };
	return std::find_if_not(text.begin(), text.end(), isDigit) == text.end();
}

TEST(IsStringIntTests, find_if_not_lambda)
{
	EXPECT_FALSE(isNumber_find_if_not_lambda("abc"));
	EXPECT_FALSE(isNumber_find_if_not_lambda("123abc"));
	EXPECT_FALSE(isNumber_find_if_not_lambda("abc123"));
	EXPECT_FALSE(isNumber_find_if_not_lambda("12abc3"));
	EXPECT_FALSE(isNumber_find_if_not_lambda("ab123c"));

	EXPECT_TRUE(isNumber_find_if_not_lambda("123"));
}
///////////////////////////////////////////////////////////////////////////////

bool isDigit(char c)
{
	return std::isdigit(c);
}

bool isNumber_find_if_not(std::string_view text)
{
	return std::find_if_not(text.begin(), text.end(), isDigit) == text.end();
}

TEST(IsStringIntTests, find_if_not)
{
	EXPECT_FALSE(isNumber_find_if_not("abc"));
	EXPECT_FALSE(isNumber_find_if_not("123abc"));
	EXPECT_FALSE(isNumber_find_if_not("abc123"));
	EXPECT_FALSE(isNumber_find_if_not("12abc3"));
	EXPECT_FALSE(isNumber_find_if_not("ab123c"));

	EXPECT_TRUE(isNumber_find_if_not("123"));
}
///////////////////////////////////////////////////////////////////////////////

// c++98 version
bool isNotDigit(char c)
{
	return !std::isdigit(c);
}

bool isNumber_find_if(const std::string& text)
{
	return std::find_if(text.begin(), text.end(), isNotDigit) == text.end();
}

TEST(IsStringIntTests, find_if)
{
	EXPECT_FALSE(isNumber_find_if("abc"));
	EXPECT_FALSE(isNumber_find_if("123abc"));
	EXPECT_FALSE(isNumber_find_if("abc123"));
	EXPECT_FALSE(isNumber_find_if("12abc3"));
	EXPECT_FALSE(isNumber_find_if("ab123c"));

	EXPECT_TRUE(isNumber_find_if("123"));
}
///////////////////////////////////////////////////////////////////////////////

// nie mam boosta, żeby sprawdzić tę wersję
// bool isNumber(const std::string& text)
// {
// 	return boost::all(text, boost::is_digit());
// }
// //---------------------------------------------------------------------------

} // namespace Tests