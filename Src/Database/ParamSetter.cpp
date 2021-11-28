#include "Database/ParamSetter.h"

#include <optional>
#include <string>

#include <sqlite/sqlite3.h>

namespace Db::Impl
{
template<>
auto setParam(sqlite3_stmt* statement, int index, std::string value) -> int // NOLINT
{
	return sqlite3_bind_text(
		statement, index, value.c_str(), value.size(), SQLITE_TRANSIENT);
}

template<>
auto setParam(sqlite3_stmt* statement, int index, const char* value) -> int
{
	std::string tmpString = value;
	return sqlite3_bind_text(
		statement, index, tmpString.c_str(), tmpString.size(), SQLITE_TRANSIENT);
}

template<>
auto setParam(sqlite3_stmt* statement, int index, int value) -> int
{
	return sqlite3_bind_int(statement, index, value);
}

template<>
auto setParam(sqlite3_stmt* statement, int index, double value) -> int
{
	return sqlite3_bind_double(statement, index, value);
}

template<>
auto setParam(sqlite3_stmt* statement, int index, std::nullopt_t) -> int
{
	return sqlite3_bind_null(statement, index);
}

} // namespace Db::Impl
