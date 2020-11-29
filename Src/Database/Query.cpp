#include "Database/Query.h"

#include <stdexcept>

#include <sqlite/sqlite3.h>

#include "Database/Database.h"

namespace Db
{
Query::Query(const std::string& sql, Db::Database* database)
	: database(database)
{
	auto dbStatus = sqlite3_prepare_v2(
		database->getHandler(), sql.c_str(), sql.size(), &statement, nullptr);

	checkForDbError(dbStatus);
	createUnsetParametersList();
}

Query::~Query()
{
	if (!statement)
		return;

	sqlite3_finalize(statement);
	statement = nullptr;
}

void Query::executeCommand() const
{
	validateAllParametersAreSet();
	auto dbStatus = sqlite3_step(statement);

	if (dbStatus == SQLITE_ROW)
		throw std::logic_error("Db: Query returned a value while executing command");

	if (dbStatus != SQLITE_DONE)
		checkForDbError(dbStatus);

	reset();
}

Dataset Query::execute() const
{
	validateAllParametersAreSet();
	auto dbStatus = sqlite3_step(statement);

	if (dbStatus != SQLITE_ROW && dbStatus != SQLITE_DONE)
		checkForDbError(dbStatus);

	return Dataset(statement, database);
}

void Query::reset() const
{
	sqlite3_reset(statement);
}

void Query::createUnsetParametersList()
{
	for (int i = 1; i <= sqlite3_bind_parameter_count(statement); ++i)
		unsetParams.insert(sqlite3_bind_parameter_name(statement, i));
}

void Query::validateAllParametersAreSet() const
{
	if (unsetParams.empty())
		return;

	throw std::logic_error(
		"Db: parameter '" + *unsetParams.begin() + "' is not set");
}

int Query::getParamIndex(const std::string& name)
{
	auto index = sqlite3_bind_parameter_index(statement, name.c_str());

	if (index == 0)
		throw std::logic_error("Db: unknown parameter: '" + name + "'");

	return index;
}

void Query::checkForDbError(int dbStatus) const
{
	using namespace std::string_literals;

	if (dbStatus != SQLITE_OK)
		throw std::logic_error("Db: "s + sqlite3_errmsg(database->getHandler()));
}

void Query::finalizeStatement()
{
	if (!statement)
		return;

	auto dbStatus = sqlite3_finalize(statement);
	statement = nullptr;
	checkForDbError(dbStatus);
}

} // namespace Db
