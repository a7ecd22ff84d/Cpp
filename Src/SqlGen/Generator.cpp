#include "SqlGen/Generator.h"

#include <iostream>
#include <ostream>
#include <string>
#include <string_view>

#include <yaml-cpp/yaml.h>

#include "fmt/core.h"
#include "yaml-cpp/node/parse.h"

namespace SqlGen
{
void Generator::registerTable(const std::string& definition)
{
	auto data = YAML::Load(definition);
	registeredTables.emplace(data["name"].as<std::string>(), data);
}

auto Generator::getRegisteredTables() -> std::vector<std::string>
{
	auto result = std::vector<std::string>();

	for (const auto& table : registeredTables)
		result.push_back(table.first);

	return result;
}

auto Generator::getCreateStatement(const std::string& name) -> std::string
{
	auto definition = registeredTables.at(name);

	auto result = fmt::format(
		"\nCREATE TABLE {0}\n(\n", definition["name"].as<std::string>());

	auto fields = definition["fields"];
	for (auto i = 0u; i < fields.size(); i++)
	{
		auto isLast = i == fields.size() - 1;
		result += getColumnDefinition(fields[i], isLast);
	}
	result += ")\n";

	return result;
}

auto Generator::getColumnDefinition(const YAML::Node& columnNode, bool isLast)
	-> std::string
{
	auto constraint = std::string();
	if (columnNode["constraint"].IsDefined())
		constraint = " " + columnNode["constraint"].as<std::string>();

	return fmt::format(
		"\t{0} {1}{2}{3}\n",
		columnNode["name"].as<std::string>(),
		columnNode["type"].as<std::string>(),
		constraint,
		isLast ? "" : ",");
}

} // namespace SqlGen
