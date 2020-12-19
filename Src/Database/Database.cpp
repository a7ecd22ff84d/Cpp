#include "Database/Database.h"

#include <stdexcept>

#include <sqlite/sqlite3.h>

namespace
{
const std::string dbError = "Database error: ";

} // namespace

namespace Db
{
Database::Database(const std::string& name)
	: handler(nullptr)
	, databaseName(name)
{
	connect(databaseName);
}

Database::~Database()
{
	disconnect();
}

void Database::connect(const std::string& name)
{
	auto dbStatus = 0;

	dbStatus = sqlite3_open(name.c_str(), &handler);

	if (dbStatus != SQLITE_OK)
		throw std::logic_error(dbError + sqlite3_errstr(dbStatus));
}

void Database::disconnect()
{
	auto dbStatus = 0;

	dbStatus = sqlite3_close(handler);

	if (dbStatus != SQLITE_OK)
		throw std::logic_error(dbError + sqlite3_errstr(dbStatus));
}

sqlite3* Database::getHandler()
{
	return handler;
}

} // namespace Db
