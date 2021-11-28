#include "Database/Dataset.h"

#include <stdexcept>
#include <string>

#include <fmt/core.h>
#include <sqlite/sqlite3.h>

#include "Database/Database.h"

namespace Db
{
Dataset::Dataset(std::shared_ptr<sqlite3_stmt> statement, Database* db) // NOLINT
	: statement(statement)
	, valueGetter(statement.get())
{
	loadColumnInfo();
	datasetEmpty = sqlite3_extended_errcode(db->getHandler()) == SQLITE_DONE;
}

auto Dataset::empty() const -> bool
{
	return datasetEmpty;
}

auto Dataset::next() -> bool
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

auto Dataset::getColumnId(const std::string& name) const -> int
{
	auto it = columnsHeader.find(name);
	if (it == columnsHeader.end())
		throw std::logic_error(fmt::format("Db: column '{0}' does not exist", name));

	return it->second;
}

} // namespace Db
