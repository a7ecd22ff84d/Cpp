
#include "Journal/Database/Database.h"

#include <fstream>
#include <iostream>

#include <fmt/core.h>

#include "Database/Query.h"

namespace Jrnl
{
Database::Database(const std::string& filename) : db(Db::Database(filename))
{
}

void Database::create()
{
	registerTable("Tables/Entry.yaml");
	Db::Query(generator.getCreateStatement("entry"), &db).executeCommand();
}

void Database::registerTable(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::logic_error(fmt::format("Could not open file {}", filename));

	auto data = std::string(
		std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	generator.registerTable(data);
}

} // namespace Jrnl