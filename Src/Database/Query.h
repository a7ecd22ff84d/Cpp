#ifndef __QUERY_H
#define __QUERY_H

#include <memory>
#include <set>

#include "Database/Database.h"
#include "Database/Dataset.h"
#include "Database/ParamSetter.h"
#include "Database/SQLite_fwd.h"

namespace Db
{
class Query
{
public:
	Query(const std::string& sql, Db::Database* database);

	void executeCommand() const;
	[[nodiscard]] auto execute() const -> Dataset;
	void reset() const;

	template<typename T>
	void setParam(const std::string& name, T value)
	{
		auto dbStatus = Db::setParam(statement.get(), getParamIndex(name), value);
		checkForDbError(dbStatus);
		unsetParams.erase(name);
	}

private:
	void createUnsetParametersList();
	void validateAllParametersAreSet() const;
	auto getParamIndex(const std::string& name) -> int;

	void checkForDbError(int dbStatus) const;
	void finalizeStatement();

private:
	Db::Database* database;
	std::shared_ptr<sqlite3_stmt> statement;
	std::set<std::string> unsetParams;
};

} // namespace Db

#endif // __QUERY_H
