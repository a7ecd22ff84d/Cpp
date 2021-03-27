#include "Core/Random/VariableRangeRng.h"

#include <chrono>

VariableRangeRng::VariableRangeRng(std::string_view seed)
{
	if (seed.empty())
		engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
	else
		engine.seed(std::hash<std::string_view>{}(seed));
}

int VariableRangeRng::getRandom(int min, int max)
{
	return distribution(
		engine, std::uniform_int_distribution<int>::param_type{min, max});
}