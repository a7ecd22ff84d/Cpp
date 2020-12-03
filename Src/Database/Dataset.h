#ifndef __DATASET_H
#define __DATASET_H

#include <map>
#include <memory>
#include <string>

#include "Database/Database.h"
#include "Database/SQLite_fwd.h"
#include "Database/ValueGetter.h"

namespace Db
{
class Dataset
{
public:
	Dataset(std::shared_ptr<sqlite3_stmt> statement, Database* db);

	bool empty() const;
	bool next();

	template<typename T>
	T get(const std::string& name)
	{
		if (empty())
			throw std::logic_error("Db: dataset is empty");

		auto columnIndex = getColumnId(name);
		return valueGetter.get<T>(columnIndex);
	}

private:
	void loadColumnInfo();
	int getColumnId(const std::string& name) const;

private:
	bool datasetEmpty;
	bool firstRow = true;
	std::shared_ptr<sqlite3_stmt> statement;
	std::map<std::string, int> columnsHeader;
	ValueGetter valueGetter;
};

} // namespace Db

#endif // __DATASET_H
