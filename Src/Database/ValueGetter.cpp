#include "Database/ValueGetter.h"

#include <stdexcept>
#include <string>

#include <fmt/core.h>
#include <sqlite/sqlite3.h>

#include "Core/Types/DemangledTypeName.h"
#include "Core/Types/IsOptional.h"
#include "Database/SQLite_fwd.h"

namespace Db
{
ValueGetter::ValueGetter(sqlite3_stmt* statement) : statement(statement)
{
}

auto ValueGetter::getColumnName(int columnId) const -> std::string
{
	return sqlite3_column_name(statement, columnId);
}

auto ValueGetter::isNullValue(int columnId) const -> bool
{
	return (char*)(sqlite3_column_text(statement, columnId)) == nullptr;
}

template<>
auto ValueGetter::getImpl(int columnId) -> int
{
	return tryToCast<int>(
		columnId, [](const std::string& value) { return stoi(value); });
}

template<>
auto ValueGetter::getImpl(int columnId) -> double
{
	return tryToCast<double>(
		columnId, [](const std::string& value) { return stod(value); });
}

template<>
auto ValueGetter::getImpl(int columnId) -> std::string
{
	return (char*)(sqlite3_column_text(statement, columnId));
}

// Sqlite_colum_xxx() cannot be used because these functions don't show me if
// value can be casted to required type. For example: casting text 'abc' to
// int returns 0
template<typename T>
auto ValueGetter::tryToCast(int columnId, CastFunction<T>* castFuncion) -> T
{
	auto value = (char*)sqlite3_column_text(statement, columnId);

	if (!value)
	{
		auto columnName = std::string(sqlite3_column_name(statement, columnId));
		throw std::logic_error(fmt::format(
			"Db: Cannot cast empty value of column '{0}' to '{1}'",
			columnName,
			Core::getDemangledTypeName<T>()));
	}

	try
	{
		return castFuncion(value);
	}
	catch (std::logic_error& err)
	{
		auto columnName = std::string(sqlite3_column_name(statement, columnId));
		throw std::logic_error(fmt::format(
			"Db: Cannot cast value '{0}' of column '{1}' to '{2}'",
			value,
			columnName,
			Core::getDemangledTypeName<T>()));
	}
}

} // namespace Db
