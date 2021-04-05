#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeGeneratorFactory.h"

void MazeGeneratorFactory::registerGenerator(std::string_view name, CreatorFunc creatorFunc)
{
	registeredCreators[name] = creatorFunc;
}

std::unique_ptr<IMazeGenerator> MazeGeneratorFactory::create(std::string_view name) const
{
	auto creatorFunc = registeredCreators.find(name);
	if (creatorFunc == registeredCreators.end())
		return nullptr;

	return creatorFunc->second();
}

std::vector<std::string_view> MazeGeneratorFactory::getRegisteredObjectNames() const
{
	auto result = std::vector<std::string_view>();

	for (auto& item : registeredCreators)
		result.push_back(item.first);

	return result;
}