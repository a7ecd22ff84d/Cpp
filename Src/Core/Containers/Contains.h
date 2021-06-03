#ifndef _CONTAINS_H
#define _CONTAINS_H

#include <algorithm>

namespace Containers
{
template<typename T, typename U>
bool contains(T container, U value)
{
	return std::find(container.begin(), container.end(), value) != container.end();
}

} // namespace Containers

#endif