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

	sqlite3* getHandler();

private:
	void connect(const std::string& name);
	void disconnect();

	sqlite3* handler;
	std::string databaseName;
};

} // namespace Db

#endif // __DATABASE_H
