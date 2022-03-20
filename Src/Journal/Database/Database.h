#ifndef JOURNAL_DATABASE_H
#define JOURNAL_DATABASE_H

#include <memory>

#include "Database/Database.h"
#include "SqlGen/Generator.h"

namespace Journal
{
class Database
{
	Database();

public:
	Database(const Database&&) = delete;
	Database(Database&&) = delete;
	auto operator=(Database &&) -> Database& = delete;
	auto operator=(const Database&) -> Database& = delete;

	static auto instance() -> Database&;

	void create(const std::string& filename);
	void open(const std::string& filename);

	auto getDatabase() -> Db::Database*;
	auto getSqlGenerator() -> SqlGen::Generator*;

private:
	std::optional<Db::Database> db;
	SqlGen::Generator generator;
};

} // namespace Journal

#endif