#include "Database/Query.h"

#include <stdexcept>

#include <sqlite/sqlite3.h>

#include "Database/Database.h"

namespace Db
{
Query::Query(const std::string& sql, Db::Database* database)
	: database(database)
	, sql(sql)
{
	auto dbStatus = sqlite3_prepare_v2(
		database->getHandler(), sql.c_str(), sql.size(), &statement, nullptr);

	checkForDbError(dbStatus);
	// parameters = std::make_unique<Parameters>(database, statement);

	// log(Log::Levels::Sql, "Query {} prepared with \"{}\"", fmt::ptr(statement), sql);
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
	sqlite3_step(statement);
	// auto dbStatus = runQuery();

	// if (dbStatus == SQLITE_ROW)
	// 	throw LogicError("Db: Query returned a value while executing command");

	// if (dbStatus != SQLITE_DONE)
	// 	checkForDbError(dbStatus);
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

	// log(Log::Levels::Sql, "Query {} unprepared", fmt::ptr(statement));
}

} // namespace Db
