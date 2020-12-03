#include "Database/Dataset.h"

#include <stdexcept>
#include <string>

#include "Database/Database.h"
#include "sqlite/sqlite3.h"

namespace Db
{
Dataset::Dataset(std::shared_ptr<sqlite3_stmt> statement, Database* db)
	: statement(statement)
	, valueGetter(statement.get())
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

	auto dbStatus = sqlite3_step(statement.get());

	if (dbStatus == SQLITE_DONE)
		sqlite3_reset(statement.get());

	return dbStatus == SQLITE_ROW;
}

void Dataset::loadColumnInfo()
{
	auto columnsCount = sqlite3_column_count(statement.get());

	for (int i = 0; i < columnsCount; i++)
	{
		std::string name = sqlite3_column_name(statement.get(), i);
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

} // namespace Db
