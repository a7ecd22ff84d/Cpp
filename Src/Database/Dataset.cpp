#include "Database/Dataset.h"

#include <string>

#include "sqlite/sqlite3.h"

namespace Db
{
Dataset::Dataset(sqlite3_stmt* statement) : stored_statement(statement)
{
	loadColumnInfo();
}

void Dataset::loadColumnInfo()
{
	auto columnsCount = sqlite3_column_count(stored_statement);

	for (int i = 0; i < columnsCount; i++)
	{
		std::string name = sqlite3_column_name(stored_statement, i);
		columnsHeader.emplace(std::make_pair(name, i));
	}
}

template<>
int Dataset::get<int>(const std::string& name)
{
	return sqlite3_column_int(stored_statement, columnsHeader.at(name));
}

template<>
std::string Dataset::get<std::string>(const std::string& name)
{
	return (char*)(sqlite3_column_text(stored_statement, columnsHeader.at(name)));
}

template<>
double Dataset::get<double>(const std::string& name)
{
	return (sqlite3_column_double(stored_statement, columnsHeader.at(name)));
}

} // namespace Db
