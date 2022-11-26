#include "Core/Mazes/RandomizedKruskals.h"

#include <algorithm>
#include <random>
#include <utility>

#include "Core/Grids/Grid.h"
#include "fmt/core.h"

namespace
{
constexpr unsigned noGroup = 0u;

} // namespace

namespace Core::Mazes
{
void RandomizedKruskals::init(
	std::size_t height, std::size_t width, const std::string& seed)
{
	bool createPassages = true;
	maze = Maze(height, width, createPassages);

	nextGroupId = 0;
	getPassagesInRandomOrder(seed);
}

auto RandomizedKruskals::getMaze() const -> const Maze&
{
	return maze;
}

auto RandomizedKruskals::step() -> bool
{
	auto v1 = maze.cellValue(passagesIt->first);
	auto v2 = maze.cellValue(passagesIt->second);

	if (v1.status == RandomizedKruskals::CellStatus::Active)
	{
		if (v1.groupId == noGroup && v2.groupId == noGroup)
		{
			createNewGroup();
		}
		else if (v1.groupId > noGroup && v2.groupId == noGroup)
		{
			addItemToGroup(v1.groupId);
		}
		else if (v1.groupId == noGroup && v2.groupId > noGroup)
		{
			addItemToGroup(v2.groupId);
		}
		else if (v1.groupId > noGroup && v2.groupId > noGroup && v1.groupId == v2.groupId)
		{
			addSolidWall(v2.groupId);
		}
		else if (v1.groupId > noGroup && v2.groupId > noGroup && v1.groupId != v2.groupId)
		{
			auto groupId = std::min(v1.groupId, v2.groupId);
			auto groupToMerge = std::max(v1.groupId, v2.groupId);
			mergeGroups(groupId, groupToMerge);
		}

		passagesIt++;
		return passagesIt != passages.end();
	}
	else
	{
		getNextPasaage();
		return true;
	}
}

void RandomizedKruskals::getPassagesInRandomOrder(const std::string& seed)
{
	passages.clear();

	passages.reserve(
		((maze.height() - 1) * maze.width())
		+ (maze.height() * (maze.width() - 1)));

	for (auto i = 0u; i < maze.width(); i++)
	{
		for (auto j = 0u; j < maze.height(); j++)
		{
			if (i < maze.width() - 1)
			{
				passages.emplace_back(
					Grids::Coordinates{i, j}, Grids::Coordinates{i + 1, j});
			}
			if (j < maze.height() - 1)
			{
				passages.emplace_back(
					Grids::Coordinates{i, j}, Grids::Coordinates{i, j + 1});
			}
		}
	}

	std::default_random_engine engine(std::hash<std::string_view>{}(seed));
	std::shuffle(passages.begin(), passages.end(), engine);

	passagesIt = passages.begin();
}

void RandomizedKruskals::getNextPasaage()
{
	maze.setCell(
		passagesIt->first,
		{RandomizedKruskals::CellStatus::Active,
		 maze.cellValue(passagesIt->first).groupId});

	maze.setCell(
		passagesIt->second,
		{RandomizedKruskals::CellStatus::Active,
		 maze.cellValue(passagesIt->second).groupId});
}

void RandomizedKruskals::createNewGroup()
{
	auto groupId = ++nextGroupId;

	if (passagesIt->type() == Grids::PassageType::South)
	{
		maze.setSouthPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::InGroup, groupId});
	}
	else
	{
		maze.setEastPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::InGroup, groupId});
	}

	maze.setCell(
		passagesIt->first, {RandomizedKruskals::CellStatus::InGroup, groupId});

	maze.setCell(
		passagesIt->second, {RandomizedKruskals::CellStatus::InGroup, groupId});
}

void RandomizedKruskals::addItemToGroup(unsigned groupId)
{
	if (passagesIt->type() == Grids::PassageType::South)
	{
		maze.setSouthPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::InGroup, groupId});
	}
	else
	{
		maze.setEastPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::InGroup, groupId});
	}

	maze.setCell(
		passagesIt->first, {RandomizedKruskals::CellStatus::InGroup, groupId});

	maze.setCell(
		passagesIt->second, {RandomizedKruskals::CellStatus::InGroup, groupId});
}

void RandomizedKruskals::addSolidWall(unsigned groupId)
{
	if (passagesIt->type() == Grids::PassageType::South)
	{
		maze.setSouthPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::Wall, noGroup});
	}
	else
	{
		maze.setEastPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::Wall, noGroup});
	}

	maze.setCell(
		passagesIt->first, {RandomizedKruskals::CellStatus::InGroup, groupId});

	maze.setCell(
		passagesIt->second, {RandomizedKruskals::CellStatus::InGroup, groupId});
}

void RandomizedKruskals::mergeGroups(unsigned groupId, unsigned groupToMerge)
{
	if (passagesIt->type() == Grids::PassageType::South)
	{
		maze.setSouthPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::InGroup, groupId});
	}
	else
	{
		maze.setEastPassage(
			*passagesIt, {RandomizedKruskals::PassageStatus::InGroup, groupId});
	}

	maze.setCell(
		passagesIt->first, {RandomizedKruskals::CellStatus::InGroup, groupId});

	maze.setCell(
		passagesIt->second, {RandomizedKruskals::CellStatus::InGroup, groupId});

	for (auto i = 0u; i < maze.height(); i++)
	{
		for (auto j = 0u; j < maze.width(); j++)
		{
			if (maze.cellValue(i, j).groupId == groupToMerge)
			{
				maze.setCell(
					i, j, {RandomizedKruskals::CellStatus::InGroup, groupId});
			}

			if (j < maze.width() - 1
				&& maze.eastPassageValue(i, j).groupId == groupToMerge)
			{
				maze.setEastPassage(
					i, j, {RandomizedKruskals::PassageStatus::InGroup, groupId});
			}
			if (i < maze.height() - 1
				&& maze.southPassageValue(i, j).groupId == groupToMerge)
			{
				maze.setSouthPassage(
					i, j, {RandomizedKruskals::PassageStatus::InGroup, groupId});
			}
		}
	}
}

} // namespace Core::Mazes
