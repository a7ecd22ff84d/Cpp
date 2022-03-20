#include "Journal/Database/InitGenerator.h"

#include <fstream>
#include <memory>

#include <fmt/format.h>

namespace
{
void registerTable(SqlGen::Generator* generator, const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::logic_error(fmt::format("Could not open file {}", filename));

	auto data = std::string(
		std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

	generator->registerTable(data);
}

} // namespace

namespace Journal
{
void initSqlGenerator(SqlGen::Generator* generator)
{
	registerTable(generator, "Tables/Entry.yaml");
}

} // namespace Journal
