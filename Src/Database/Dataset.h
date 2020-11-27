#ifndef __DATASET_H
#define __DATASET_H

#include <map>
#include <string>

#include "Database/SQLite_fwd.h"

namespace Db
{
class Dataset
{
public:
	Dataset(sqlite3_stmt* statement);

	template<typename T>
	T get(const std::string& name);

private:
	void loadColumnInfo();

private:
	sqlite3_stmt* stored_statement;
	std::map<std::string, int> columnsHeader;
};

} // namespace Db

#endif // __DATASET_H
