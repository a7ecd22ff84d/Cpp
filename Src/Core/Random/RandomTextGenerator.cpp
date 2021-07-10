#include "RandomTextGenerator.h"

#include <algorithm>

namespace Random
{
std::string generateRandomText(size_t length)
{
	// https://stackoverflow.com/questions/2146792/how-do-you-generate-random-strings-in-c
	auto getRandomChar = []() -> char
	{
		const char charset[] =
			"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		const size_t maxIndex = (sizeof(charset) - 1);
		return charset[rand() % maxIndex];
	};

	std::string str(length, 0);
	std::generate_n(str.begin(), length, getRandomChar);
	return str;
}

} // namespace Random
