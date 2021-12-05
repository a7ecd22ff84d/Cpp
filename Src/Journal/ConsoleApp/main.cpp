#include <filesystem>
#include <iostream>

#include "Journal/Database/Database.h"

auto main(int argv, char** argc) -> int
{
	std::cout << "\n\nTest\n\n";

	auto databaseFile = "JournalDatabase.db";

	std::filesystem::remove(databaseFile);
	auto database = Jrnl::Database(databaseFile);
	database.create();

	return 0;
}