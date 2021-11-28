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

private:
	auto getColumnDefinition(const YAML::Node& columnNode, bool isLast)
		-> std::string;

private:
	std::map<std::string, YAML::Node> registeredTables;
};

} // namespace SqlGen

#endif