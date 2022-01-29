#include "Journal/App/DatabaseManager.h"

#include <memory>

namespace Jrnl
{

void DatabaseManager::create(const QString& filename)
{
	auto database = std::make_unique<Database>(filename.toStdString());
	database->create();
}

void DatabaseManager::open(const QString& filename)
{
}

} // namespace Jrnl