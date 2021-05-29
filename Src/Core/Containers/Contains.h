#ifndef _CONTAINS_H
#define _CONTAINS_H

#include <algorithm>
namespace Containers
{
// template<typename T>
// bool contains(T container, typename T::value_type value)
// {
// 	return std::find(container.begin(), container.end(), value) != container.end();
// }

template<typename T, typename U>
bool contains(T container, U value)
{
	return true;
	// return std::find(container.begin(), container.end(), value) != container.end();
}

} // namespace Containers

#endif