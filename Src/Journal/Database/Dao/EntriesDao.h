#ifndef ENTRIES_DAO_H
#define ENTRIES_DAO_H

#include "Database/Database.h"
#include "Journal/Database/Entities/Entry.h"
#include "SqlGen/Generator.h"

namespace Journal
{
class EntriesDao
{
public:
	EntriesDao(Db::Database* db, SqlGen::Generator* generator);

	auto getEntries() -> std::vector<Entities::Entry>;

private:
	Db::Database* db;
	SqlGen::Generator* generator;
};
} // namespace Journal

#endif