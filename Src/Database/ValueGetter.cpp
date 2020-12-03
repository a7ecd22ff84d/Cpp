#include "Database/ValueGetter.h"

#include <string>

#include <sqlite/sqlite3.h>

#include "Database/SQLite_fwd.h"


namespace Db
{
ValueGetter::ValueGetter(sqlite3_stmt* statement) : statement(statement)
{
}

template<>
int ValueGetter::get(int columnId)
{
	return sqlite3_column_int(statement, columnId);
}

template<>
std::string ValueGetter::get(int columnId)
{
	return (char*)(sqlite3_column_text(statement, columnId));
}

template<>
double ValueGetter::get(int columnId)
{
	return sqlite3_column_double(statement, columnId);
}

} // namespace Db
