
#include "Journal/Database/Database.h"

#include "Database/Query.h"
#include "Journal/Database/InitGenerator.h"

namespace Journal
{

Database::Database()
{
	initSqlGenerator(&generator);
}

auto Database::instance() -> Database&
{

	static Database database;
	return database;
}

void Database::create(const std::string& filename)
{
	db = Db::Database(filename);
	Db::Query(generator.getCreateStatement("entry"), &db.value()).executeCommand();
}

void Database::open(const std::string& filename)
{
	db = Db::Database(filename);
}

auto Database::getDatabase() -> Db::Database*
{
	return &db.value();
}

auto Database::getSqlGenerator() -> SqlGen::Generator*
{
	return &generator;
}

} // namespace Journal