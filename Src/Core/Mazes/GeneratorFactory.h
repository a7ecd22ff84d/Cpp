#ifndef __MAZE_GENERATOR_FACTORY_H
#define __MAZE_GENERATOR_FACTORY_H

#include <map>
#include <memory>
#include <string_view>

#include "Core/Mazes/IMazeGenerator.h"

namespace Mazes
{
class GeneratorFactory
{
	using CreatorFunc = std::unique_ptr<IMazeGenerator> (*)();

public:
	void registerGenerator(std::string_view name, CreatorFunc creatorFunc);
	std::unique_ptr<IMazeGenerator> create(std::string_view name) const;
	std::vector<std::string_view> getRegisteredObjectNames() const;

private:
	std::map<std::string_view, CreatorFunc> registeredCreators;
};

} // namespace Mazes

#endif