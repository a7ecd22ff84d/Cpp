#ifndef __MAIN_TABLE_H
#define __MAIN_TABLE_H

#include <iterator>
#include <string>
#include <vector>

#include "Database/Database.h"

namespace TestTools
{
struct TestTableRow
{
	int id;
	int first;
	std::string second;
	double third;
};

using TestTableRows = std::vector<TestTableRow>;

void dropTestTable(Db::Database* db);
void createTestTable(Db::Database* db);
void fillTestTable(TestTableRows data, Db::Database* db);
TestTableRows getTestTabeContent(Db::Database* db);

} // namespace TestTools

#endif // __MAIN_TABLE_H
