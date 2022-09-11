#pragma once

namespace StringTools
{

// stdcmp is not constexpr :(
constexpr auto cstrCompare(const char* lhs, const char* rhs) -> bool
{
	auto i = 0;

	while (lhs[i] != 0 and rhs[i] != 0)
	{
		if (lhs[i] != rhs[i])
			return false;

		i++;
	}

	if (lhs[i] != rhs[i])
		return false;

	return true;
}

} // namespace StringTools