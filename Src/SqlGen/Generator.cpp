#include "SqlGen/Generator.h"

#include <string>
#include <string_view>

#include "fmt/core.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

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

auto Generator::getSelectStatement(const std::string& name) -> std::string
{
	auto definition = registeredTables.at(name);
	auto result = std::string("\nSELECT\n");
	result += getColumnList(definition["fields"]);
	result += fmt::format("FROM {0}\n", name);
	return result;
}

auto Generator::getInsertStatement(const std::string& name) -> std::string
{
	auto definition = registeredTables.at(name);
	auto fields = definition["fields"];

	auto result = fmt::format("\nINSERT INTO {0}\n(\n", name);
	result += getColumnList(fields);
	result += ")\nVALUES\n(\n";
	result += getColumnList(fields, ":");
	result += ")\n";

	return result;
}

auto Generator::getUpdateStatement(const std::string& name) -> std::string
{
	auto result = fmt::format("\nUPDATE {0}\nSET\n", name);
	auto primaryKey = std::string("");

	auto fields = registeredTables.at(name)["fields"];
	for (auto i = 0u; i < fields.size(); i++)
	{
		auto field = fields[i];
		auto constraint = field["constraint"];
		if (constraint.IsScalar() && constraint.as<std::string>() == "PRIMARY KEY")
		{
			primaryKey = field["name"].as<std::string>();
			continue;
		}

		auto isLast = i == fields.size() - 1;
		result += fmt::format(
			"\t{0} = :{0}{1}\n", field["name"].as<std::string>(), isLast ? "" : ",");
	}
	result += fmt::format("WHERE\n\t{0} = :{0}\n", primaryKey);

	return result;
}

auto Generator::getColumnDefinition(const YAML::Node& columnNode, bool isLast) const
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

auto Generator::getColumnList(const YAML::Node& fields, const std::string& prefix) const
	-> std::string
{
	std::string result;
	for (auto i = 0u; i < fields.size(); i++)
	{
		auto isLast = i == fields.size() - 1;
		result += fmt::format(
			"\t{0}{1}{2}\n",
			prefix,
			fields[i]["name"].as<std::string>(),
			isLast ? "" : ",");
	}

	return result;
}

} // namespace SqlGen
