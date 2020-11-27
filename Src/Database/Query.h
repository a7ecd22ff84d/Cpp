#ifndef __QUERY_H
#define __QUERY_H

#include "Database/Database.h"
#include "Database/Dataset.h"
#include "Database/SQLite_fwd.h"

namespace Db
{
class Query
{
public:
	Query(const std::string& sql, Db::Database* database);
	~Query();

	void executeCommand() const;
	Dataset execute();

private:
	void checkForDbError(int dbStatus) const;
	void finalizeStatement();

private:
	Db::Database* database;
	std::string sql;
	
	sqlite3_stmt* statement;
};

} // namespace Db

#endif // __QUERY_H
