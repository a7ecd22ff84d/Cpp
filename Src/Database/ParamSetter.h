#ifndef __PARAM_SETTER_H
#define __PARAM_SETTER_H

#include "Database/SQLite_fwd.h"

namespace Db
{
template<typename T>
int setParam(sqlite3_stmt* statement, int index, T value);

} // namespace Db

#endif // __PARAM_SETTER_H
