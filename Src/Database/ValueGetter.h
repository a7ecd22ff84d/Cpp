#ifndef __VALUE_GETTER_H
#define __VALUE_GETTER_H

#include <optional>
#include <string>

#include "Core/Types/IsOptional.h"
#include "Database/SQLite_fwd.h"

namespace Db
{
class ValueGetter
{
	template<typename T>
	using CastFunction = T(const std::string&);

public:
	ValueGetter(sqlite3_stmt* statement);

	template<typename T>
	T get(int columnIndex)
	{
		if constexpr (Types::isOptional_v<T>)
		{
			if (isNullValue(columnIndex))
				return std::nullopt;
			else
				return getImpl<typename T::value_type>(columnIndex);
		}
		else
		{
			return getImpl<T>(columnIndex);
		}
	}

private:
	std::string getColumnName(int columnId) const;
	bool isNullValue(int columnId) const;

	template<typename T>
	T getImpl(int columnIndex);

	template<typename T>
	T tryToCast(int columnId, CastFunction<T>* castFuncion);

private:
	sqlite3_stmt* statement;
};

} // namespace Db

#endif // __VALUE_GETTER_H
