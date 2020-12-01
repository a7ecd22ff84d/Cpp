#ifndef __DATASET_H
#define __DATASET_H

#include <map>
#include <memory>
#include <string>

#include "Database/Database.h"

#include "Database/SQLite_fwd.h"

namespace Db
{
class Dataset
{
public:
	Dataset(std::shared_ptr<sqlite3_stmt> statement, Database* db);

	bool empty() const;
	bool next();

	template<typename T>
	T get(const std::string& name);

private:
	void loadColumnInfo();
	int getColumnId(const std::string& name) const;

private:
	bool datasetEmpty;
	bool firstRow = true;
	std::shared_ptr<sqlite3_stmt> statement;
	std::map<std::string, int> columnsHeader;
};

} // namespace Db

#endif // __DATASET_H
