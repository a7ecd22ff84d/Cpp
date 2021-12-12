#include "Core/Date/DateSqlParam.h"

#include <istream>

#include <sqlite/sqlite3.h>

#include "date/date.h"

namespace Db
{
template<>
auto setParam(sqlite3_stmt* statement, int index, date::year_month_day value) -> int
{
	auto txt = date::format("%F", value);
	return sqlite3_bind_text(
		statement, index, txt.c_str(), txt.size(), SQLITE_TRANSIENT);
}

template<>
auto ValueGetter::getImpl(int columnIndex) -> date::year_month_day
{
	auto result = date::year_month_day();
	std::istringstream ss{getImpl<std::string>(columnIndex)};
	ss >> date::parse("%F", result);

	return result;
}

} // namespace Db
