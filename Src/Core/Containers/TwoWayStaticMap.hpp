#ifndef TWO_WAY_STATIC_MAP_H
#define TWO_WAY_STATIC_MAP_H

#include <algorithm>
#include <array>
#include <cstring>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace Containers
{
constexpr auto compareCstr(const char* lhs, const char* rhs) -> bool
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

	constexpr auto toSv(const T& value) const -> const char*
	{
		for (auto i = 0u; i < data.size(); i++)
		{
			if (data[i].first == value)
				return data[i].second;
		}
	}

	constexpr auto toEnum(const char* value) const -> T
	{
		for (auto i = 0u; i < data.size(); i++)
		{
			if (compareCstr(data[i].second, value))
				return data[i].first;
		}
	}

private:
	EnumDataInt data;
};

// template<typename T>
// constexpr auto createEnumMapper(const std::vector<std::pair<T, std::string>>& vec)
// {
// 	constexpr auto length = std::max(
// 		vec.begin(),
// 		vec.end(),
// 		[](const std::pair<T, std::string>& lhs,
// 		   const std::pair<T, std::string>& rhs) {
// 			return lhs.second.size() < rhs.second.size();
// 		});

// 	return EnumMapper<T, vec.size(), length>{vec};
// }

} // namespace Containers

#endif