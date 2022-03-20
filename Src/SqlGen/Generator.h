#ifndef GENERATOR_H
#define GENERATOR_H

#include <map>
#include <string>
#include <vector>

#include "yaml-cpp/node/node.h"

namespace SqlGen
{
class Generator
{
public:
	void registerTable(const std::string& definition);

	auto getRegisteredTables() -> std::vector<std::string>;
	auto getCreateStatement(const std::string& name) -> std::string;
	auto getSelectStatement(const std::string& name) -> std::string;
	auto getInsertStatement(const std::string& name) -> std::string;
	auto getUpdateStatement(const std::string& name) -> std::string;

private:
	[[nodiscard]] auto getColumnDefinition(const YAML::Node& columnNode, bool isLast) const
		-> std::string;

	[[nodiscard]] auto getColumnList(
		const YAML::Node& fields, const std::string& prefix = "") const
		-> std::string;

private:
	std::map<std::string, YAML::Node> registeredTables;
};

} // namespace SqlGen

#endif