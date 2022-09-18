#pragma once

#include <array>
#include <stdexcept>
#include <string_view>

#include "Core/StringTools/CstrCompare.hpp"

namespace Containers
{
template<typename T, int S>
using EnumData = std::array<std::pair<T, const char*>, S>;

template<typename T, int S, int L>
class EnumMapper
{
	using EnumToStr = std::pair<T, const char*>;
	using EnumDataInt = std::array<EnumToStr, S>;

public:
	constexpr EnumMapper(const EnumData<T, S>& vec) : data(vec)
	{
	}

	constexpr auto toString(const T& value) const -> std::string_view
	{
		for (auto i = 0u; i < data.size(); i++)
		{
			if (data[i].first == value)
				return data[i].second;
		}

		throw std::logic_error("Unknown enum value");
	}

	[[nodiscard]] constexpr auto toEnum(const char* value) const -> T
	{
		for (auto i = 0u; i < data.size(); i++)
		{
			if (StringTools::cstrCompare(data[i].second, value))
				return data[i].first;
		}

		throw std::logic_error(std::string("Value") + value + " does not exist");
	}

private:
	EnumDataInt data;
};

} // namespace Containers
