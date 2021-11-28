#ifndef __PARAM_SETTER_H
#define __PARAM_SETTER_H

#include <optional>

#include "Core/Types/IsOptional.h"
#include "Database/SQLite_fwd.h"

namespace Db
{
namespace Impl
{
template<typename T>
auto setParam(sqlite3_stmt* statement, int index, T value) -> int;

} // namespace Impl

template<typename T>
auto setParam(sqlite3_stmt* statement, int index, T value) -> int
{
	if constexpr (Types::isOptional_v<T>)
	{
		if (value.has_value())
			return Impl::setParam(statement, index, *value);
		else
			return Impl::setParam(statement, index, std::nullopt);
	}
	else
	{
		return Impl::setParam(statement, index, value);
	}
}

} // namespace Db

#endif // __PARAM_SETTER_H
