#include "Database/ValueGetter.h"

#include <stdexcept>
#include <string>

#include <sqlite/sqlite3.h>

#include "Core/Types/DemangledTypeName.h"
#include "Core/Types/IsOptional.h"
#include "Database/SQLite_fwd.h"


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
	return tryToCast<int>(columnId, [](const std::string& value) {
		return stoi(value);
	});
}

template<>
double ValueGetter::getImpl(int columnId)
{
	return tryToCast<double>(columnId, [](const std::string& value) {
		return stod(value);
	});
}

template<>
std::string ValueGetter::getImpl(int columnId)
{
	return (char*)(sqlite3_column_text(statement, columnId));
}

// Sqlite_colum_xxx() cannot be used because these functions don't show me if
// value can be casted to required type. For example: casting text 'abc' to
// int returns 0 
template<typename T>
T ValueGetter::tryToCast(int columnId,  CastFunction<T>* castFuncion)
{
	auto value = (char*)sqlite3_column_text(statement, columnId);

	if (!value)
	{
		auto columnName = std::string(sqlite3_column_name(statement, columnId));
		throw std::logic_error(
			"Db: Cannot cast empty value of column '" + columnName + "' to '"
			+ Core::getDemangledTypeName<T>() + "'");
	}

	try
	{
		return castFuncion(value);
	}
	catch (std::logic_error& err)
	{
		auto columnName = std::string(sqlite3_column_name(statement, columnId));
		throw std::logic_error(
			"Db: Cannot cast value '" + std::string(value) + "' of column '"
			+ columnName + "' to '" + Core::getDemangledTypeName<T>() + "'");
	}
}

} // namespace Db
