#include "Journal/App/DatabaseManager.h"
#include <memory>

namespace Jrnl
{
// auto DatabaseManager::create(const std::string& filename) -> std::unique_ptr<Database>
// {
// 	auto database = std::make_unique<Database>(filename);
// 	database->create();

// 	return database;
// }

void DatabaseManager::create(const QString& filename) 
{
	auto database = std::make_unique<Database>(filename.toStdString());
	database->create();
}

} // namespace Jrnl