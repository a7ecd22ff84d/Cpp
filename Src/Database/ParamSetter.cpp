#include "Database/ParamSetter.h"

#include <string>

#include "sqlite/sqlite3.h"

namespace Db
{
template<>
int setParam(sqlite3_stmt* statement, int index, std::string value)
{
	return sqlite3_bind_text(
		statement, index, value.c_str(), value.size(), SQLITE_TRANSIENT);
}

template<>
int setParam(sqlite3_stmt* statement, int index, const char* value)
{
	std::string tmpString = value;
	return sqlite3_bind_text(
		statement, index, tmpString.c_str(), tmpString.size(), SQLITE_TRANSIENT);
}

template<>
int setParam(sqlite3_stmt* statement, int index, int value)
{
	return sqlite3_bind_int(statement, index, value);
}

template<>
int setParam(sqlite3_stmt* statement, int index, double value)
{
	return sqlite3_bind_double(statement, index, value);
}

} // namespace Db
