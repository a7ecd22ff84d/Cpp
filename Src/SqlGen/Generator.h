#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <vector>

namespace SqlGen
{
class Generator
{
public:
	void registerTable(const std::string& definition);

	auto getRegisteredTables() -> std::vector<std::string>;

public:
	std::vector<std::string> registeredTables;
};

} // namespace SqlGen

#endif