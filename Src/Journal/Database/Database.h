#ifndef REGISTER_TABLES_H
#define REGISTER_TABLES_H

#include "Database/Database.h"
#include "SqlGen/Generator.h"

namespace Jrnl
{
class Database
{
public:
	Database(const std::string& filename);

	// void open();
	void create();

private:
	void registerDatabases();
	void registerTable(const std::string& filename);

private:
	// std::string filename;
	SqlGen::Generator generator;
	Db::Database db;
};

} // namespace Jrnl

#endif