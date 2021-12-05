#ifndef REGISTER_TABLES_H
#define REGISTER_TABLES_H

#include <memory>

namespace Jrnl
{
class Database
{
	class DatabaseImpl;

public:
	Database(const std::string& filename);
	void create();

private:
	std::shared_ptr<DatabaseImpl> impl;
};

} // namespace Jrnl

#endif