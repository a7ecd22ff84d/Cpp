#include "Database/ValueGetter.h"

#include <stdexcept>
#include <string>

#include <sqlite/sqlite3.h>

#include "Core/Types/DemangledTypeName.h"
#include "Database/SQLite_fwd.h"

namespace
{
template<typename T>
using CastFunction = T(const std::string&);

template<typename T>
T tryToCast(const std::string& name, const std::string& value, CastFunction<T>* castFuncion)
{
	if (value.empty())
	{
		throw std::logic_error("Db: Cannot cast empty value "
						"of column '" + name + "' "
						"to '" + Core::getDemangledTypeName<T>() + "'");
	}

	try
	{
		return castFuncion(value);
	}
	catch (std::logic_error& err)
	{
		throw std::logic_error("Db: Cannot cast value '" + value + "' "
						"of column '" + name + "' "
						"to '" + Core::getDemangledTypeName<T>() + "'");
	}
}

} // namespace

namespace Db
{
ValueGetter::ValueGetter(sqlite3_stmt* statement) : statement(statement)
{
}

std::string ValueGetter::getColumnName(int columnId) const
{
	return sqlite3_column_name(statement, columnId);
}

bool ValueGetter::isNullValue(int columnId) const
{
	return (char*)(sqlite3_column_text(statement, columnId)) == nullptr;
}

template<>
int ValueGetter::getImpl(int columnId)
{
	auto value = (char*)sqlite3_column_text(statement, columnId);
	auto castFunc = [](const std::string& value) { return stoi(value); };
	return tryToCast<int>(getColumnName(columnId), value, castFunc);
}

template<>
double ValueGetter::getImpl(int columnId)
{
	auto value = (char*)sqlite3_column_text(statement, columnId);
	auto castFunc = [](const std::string& value) { return stod(value); };
	return tryToCast<double>(getColumnName(columnId), value, castFunc);
}

template<>
std::string ValueGetter::getImpl(int columnId)
{
	return (char*)(sqlite3_column_text(statement, columnId));
}

} // namespace Db
