#include "Journal/Database/Dao/EntriesDao.h"

#include <string>

#include "Core/Date/DateSqlParam.h"
#include "Database/Query.h"

namespace
{
using date::March;
using date::year;

} // namespace

namespace Journal
{
EntriesDao::EntriesDao(Db::Database* db, SqlGen::Generator* generator)
	: db(db)
	, generator(generator)
{
}

auto EntriesDao::getEntries() -> std::vector<Entities::Entry>
{
	auto qr = Db::Query(generator->getSelectStatement("entry"), db).execute();
	std::vector<Entities::Entry> entries;

	while (qr.next())
	{
		auto& entry = entries.emplace_back();
		entry.setId(qr.get<int>("id"));
		entry.setTitle(qr.get<std::string>("title"));
		entry.setEntryDate(qr.get<date::year_month_day>("entryDate"));
	}

	return entries;
}

} // namespace Journal