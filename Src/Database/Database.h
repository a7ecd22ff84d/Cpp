#ifndef __DATABASE_H
#define __DATABASE_H

#include <string>

#include "Database/SQLite_fwd.h"

namespace Db
{
class Database
{
public:
	Database(const std::string& name);
	~Database();

	auto getHandler() -> sqlite3*;

private:
	void connect(const std::string& name);
	void disconnect();

	sqlite3* handler;
	std::string databaseName;
};

} // namespace Db

#endif // __DATABASE_H
