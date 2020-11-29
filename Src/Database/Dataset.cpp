#include "Database/Dataset.h"

#include <stdexcept>
#include <string>

#include "Database/Database.h"
#include "sqlite/sqlite3.h"

namespace Db
{
Dataset::Dataset(sqlite3_stmt* statement, Database* db)
	: stored_statement(statement)
{
	loadColumnInfo();

	datasetEmpty = sqlite3_extended_errcode(db->getHandler()) == SQLITE_DONE;
}

bool Dataset::empty() const
{
	return datasetEmpty;
}

bool Dataset::next()
{
	if (firstRow)
	{
		firstRow = false;
		return !empty();
	}

	return sqlite3_step(stored_statement) == SQLITE_ROW;
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

int Dataset::getColumnId(const std::string& name) const
{
	auto it = columnsHeader.find(name);
	if (it == columnsHeader.end())
		throw std::logic_error("Db: column '" + name + "' does not exist");

	return it->second;
}

// gettery - wyeksmitować do innego pliku
template<>
int Dataset::get<int>(const std::string& name)
{
	if (empty())
		throw std::logic_error("Db: dataset is empty");

	return sqlite3_column_int(stored_statement, getColumnId(name));
}

template<>
std::string Dataset::get<std::string>(const std::string& name)
{
	if (empty())
		throw std::logic_error("Db: dataset is empty");

	return (char*)(sqlite3_column_text(stored_statement, getColumnId(name)));
}

template<>
double Dataset::get<double>(const std::string& name)
{
	if (empty())
		throw std::logic_error("Db: dataset is empty");

	return (sqlite3_column_double(stored_statement, getColumnId(name)));
}

} // namespace Db
