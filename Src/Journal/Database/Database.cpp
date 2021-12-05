
#include "Journal/Database/Database.h"

#include <fstream>
#include <iostream>

#include <fmt/core.h>

#include "Database/Database.h"
#include "Database/Query.h"
#include "SqlGen/Generator.h"

namespace Jrnl
{
class Database::DatabaseImpl
{
public:
	DatabaseImpl(const std::string& filename) : db(Db::Database(filename)){};

	void create()
	{
		registerTable("Tables/Entry.yaml");
		Db::Query(generator.getCreateStatement("entry"), &db).executeCommand();
	}

	void registerTable(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
			throw std::logic_error(fmt::format("Could not open file {}", filename));

		auto data = std::string(
			std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

		generator.registerTable(data);
	}

private:
	SqlGen::Generator generator;
	Db::Database db;
};

Database::Database(const std::string& filename)
	: impl(std::make_shared<DatabaseImpl>(filename))
{
}

void Database::create()
{
	impl->create();
}

} // namespace Jrnl