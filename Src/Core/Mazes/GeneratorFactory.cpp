#include "Core/Mazes/GeneratorFactory.h"

namespace Mazes
{
void GeneratorFactory::registerGenerator(std::string_view name, CreatorFunc creatorFunc)
{
	registeredCreators[name] = creatorFunc;
}

std::unique_ptr<IMazeGenerator> GeneratorFactory::create(std::string_view name) const
{
	auto creatorFunc = registeredCreators.find(name);
	if (creatorFunc == registeredCreators.end())
		return nullptr;

	return creatorFunc->second();
}

std::vector<std::string_view> GeneratorFactory::getRegisteredObjectNames() const
{
	auto result = std::vector<std::string_view>();

	for (auto& item : registeredCreators)
		result.push_back(item.first);

	return result;
}

} // namespace Mazes