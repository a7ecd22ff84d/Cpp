#include "Core/Mazes/RandomizedKruskals.h"

#include <iostream>
#include <utility>

#include "Core/Mazes/Maze.h"

namespace Mazes
{
void RandomizedKruskals::initNewMaze(const GeneratorContext& context)
{
	rng = VariableRangeRng(context.seed);

	maze = Maze();
	maze.width = context.width;
	maze.height = context.height;

	maze.cellStatuses = std::vector<std::vector<CellStatus>>(
		context.height,
		std::vector<CellStatus>(context.width, CellStatus::notVisited));

	edges.clear();
	cellGroups.clear();
	for (unsigned row = 0; row < maze.height; row++)
	{
		for (unsigned column = 0; column < maze.width; column++)
			addCellEdges(row, column);
	}
}

bool RandomizedKruskals::step()
{
	if (!maze.passages.empty())
	{
		setCellStatus(previousPassage.first, CellStatus::visited);
		setCellStatus(previousPassage.second, CellStatus::visited);
	}

	if (edges.empty())
		return false;

	auto it = getRandomEdge();

	auto firstCellGroup = getCellGroup(it->first);
	auto secondCellGroup = getCellGroup(it->second);

	auto noneGroup = cellGroups.end();

	if (firstCellGroup == noneGroup && secondCellGroup == noneGroup)
	{
		createGroup(*it);
		maze.passages.emplace_back(*it);
	}
	else if (firstCellGroup == noneGroup && secondCellGroup != noneGroup)
	{
		secondCellGroup->insert(it->first);
		maze.passages.emplace_back(*it);
	}
	else if (firstCellGroup != noneGroup && secondCellGroup == noneGroup)
	{
		firstCellGroup->insert(it->second);
		maze.passages.emplace_back(*it);
	}
	else if(firstCellGroup != secondCellGroup && firstCellGroup != noneGroup)
	{
		mergeGroups(firstCellGroup, secondCellGroup);
		maze.passages.emplace_back(*it);
	}

	setCellStatus(it->first, CellStatus::active);
	setCellStatus(it->second, CellStatus::active);
	previousPassage = *it;

	edges.erase(it);

	return true;
}

const Maze& RandomizedKruskals::getMaze() const
{
	return maze;
}

void RandomizedKruskals::addCellEdges(unsigned row, unsigned column)
{
	if (column < maze.width - 1)
	{
		edges.emplace(std::make_pair(
			Coordinates{row, column}, Coordinates{row, column + 1}));
	}

	if (row < maze.height - 1)
	{
		edges.emplace(std::make_pair(
			Coordinates{row, column}, Coordinates{row + 1, column}));
	}
}

std::set<RandomizedKruskals::Edge>::iterator RandomizedKruskals::getRandomEdge()
{
	// https://stackoverflow.com/questions/3052788/how-to-select-a-random-element-in-stdset
	auto it = std::begin(edges);
	auto size = edges.size();
	std::advance(it, rng.getRandom(0, size - 1));
	return it;
}

void RandomizedKruskals::setCellStatus(Coordinates cell, CellStatus status)
{
	maze.cellStatuses[cell.row][cell.column] = status;
}

RandomizedKruskals::CellGroups::iterator RandomizedKruskals::getCellGroup(Coordinates cell)
{
	for (auto it = cellGroups.begin(); it != cellGroups.end(); ++it)
	{
		auto& group = *it;

		if (group.find(cell) != group.end())
			return it;
	}

	return cellGroups.end();
}

void RandomizedKruskals::createGroup(Passage cells)
{
	cellGroups.emplace_back(std::set<Coordinates>{cells.first, cells.second});
}

void RandomizedKruskals::mergeGroups(
	RandomizedKruskals::CellGroups::iterator first,
	RandomizedKruskals::CellGroups::iterator second)
{
	first->insert(second->begin(), second->end());
	second->clear();
}

} // namespace Mazes
