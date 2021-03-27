#ifndef __VARIABLE_RANGE_RNG_H
#define __VARIABLE_RANGE_RNG_H

#include <random>
#include <string_view>

class VariableRangeRng
{
public:
	VariableRangeRng(std::string_view seed = "");

	int getRandom(int min, int max);

private:
	std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution;
};

#endif //__VARIABLE_RANGE_RNG_H