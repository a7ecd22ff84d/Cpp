#ifndef DATE_SQL_PARAM_H
#define DATE_SQL_PARAM_H

#include <date/date.h>

#include "Database/ParamSetter.h"
#include "Database/ValueGetter.h"
#include "Database/SQLite_fwd.h"

namespace Db
{
template<>
auto setParam(sqlite3_stmt* statement, int index, date::year_month_day value)
	-> int;

template<>
auto ValueGetter::getImpl(int columnIndex) -> date::year_month_day;

} // namespace Db

#endif