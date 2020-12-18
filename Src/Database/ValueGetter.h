#ifndef __VALUE_GETTER_H
#define __VALUE_GETTER_H

#include <string>

#include "Database/SQLite_fwd.h"

namespace Db
{
class ValueGetter
{
public:
	ValueGetter(sqlite3_stmt* statement);

	template<typename T>
	T get(int columnIndex);

private:
	std::string getColumnName(int columnId) const;

private:
	sqlite3_stmt* statement;
};

} // namespace Db

#endif // __VALUE_GETTER_H
