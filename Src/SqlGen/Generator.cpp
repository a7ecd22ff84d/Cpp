#include "SqlGen/Generator.h"

#include <iostream>
#include <ostream>
#include <string>

#include <nlohmann/json.hpp>

namespace SqlGen
{
void Generator::registerTable(const std::string& definition)
{
	auto j = nlohmann::json::parse(definition);
	registeredTables.emplace_back(j["name"].get<std::string>());
}

auto Generator::getRegisteredTables() -> std::vector<std::string>
{
	return registeredTables;
}

} // namespace SqlGen
