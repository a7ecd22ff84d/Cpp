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

	[[nodiscard]] auto empty() const -> bool;
	auto next() -> bool;

	template<typename T>
	auto get(const std::string& name) -> T
	{
		if (empty())
			throw std::logic_error("Db: dataset is empty");

		auto columnIndex = getColumnId(name);
		return valueGetter.get<T>(columnIndex);
	}

private:
	void loadColumnInfo();
	[[nodiscard]] auto getColumnId(const std::string& name) const -> int;

private:
	bool datasetEmpty;
	bool firstRow = true;
	std::shared_ptr<sqlite3_stmt> statement;
	std::map<std::string, int> columnsHeader;
	ValueGetter valueGetter;
};

} // namespace Db

#endif // __DATASET_H
