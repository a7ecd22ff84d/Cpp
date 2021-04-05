#include "Core/Mazes/RandomizedKruskals.h"

#include <algorithm>
#include <utility>

#include "Core/Mazes/BaseGenerator.h"
#include "Core/Mazes/Maze.h"

namespace Mazes
{
void RandomizedKruskals::initNewMaze(const GeneratorContext& context)
{
	BaseGenerator::initNewMaze(context);

	edges.clear();
	cellGroups.clear();
	previousPassage.reset();

	for (unsigned row = 0; row < maze.height; row++)
	{
		for (unsigned column = 0; column < maze.width; column++)
			addCellEdges(row, column);
	}
}

bool RandomizedKruskals::step()
{
	if (previousPassage.has_value())
	{
		setCellStatus(previousPassage->first, CellStatus::visited);
		setCellStatus(previousPassage->second, CellStatus::visited);
	}

	if (edges.empty())
		return false;

	auto it = getRandomEdge();
	setCellStatus(it->first, CellStatus::active);
	setCellStatus(it->second, CellStatus::active);
	previousPassage = *it;

	handleCellGroups(it);
	edges.erase(it);

	return true;
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

std::set<Passage>::iterator RandomizedKruskals::getRandomEdge()
{
	// https://stackoverflow.com/questions/3052788/how-to-select-a-random-element-in-stdset
	auto it = std::begin(edges);
	auto size = edges.size();
	std::advance(it, rng.getRandom(0, size - 1));
	return it;
}

void RandomizedKruskals::setCellStatus(const Coordinates& cell, CellStatus status)
{
	maze.cellStatuses[cell.row][cell.column] = status;
}

void RandomizedKruskals::handleCellGroups(std::set<Passage>::iterator edge)
{
	auto firstCellGroup = getCellGroup(edge->first);
	auto secondCellGroup = getCellGroup(edge->second);

	auto noneGroup = cellGroups.end();

	if (firstCellGroup == noneGroup && secondCellGroup == noneGroup)
	{
		createGroup(*edge);
		maze.passages.emplace_back(*edge);
	}
	else if (firstCellGroup == noneGroup && secondCellGroup != noneGroup)
	{
		secondCellGroup->insert(edge->first);
		maze.passages.emplace_back(*edge);
	}
	else if (firstCellGroup != noneGroup && secondCellGroup == noneGroup)
	{
		firstCellGroup->insert(edge->second);
		maze.passages.emplace_back(*edge);
	}
	else if (firstCellGroup != secondCellGroup && firstCellGroup != noneGroup)
	{
		mergeGroups(firstCellGroup, secondCellGroup);
		maze.passages.emplace_back(*edge);
	}
}

RandomizedKruskals::CellGroups::iterator RandomizedKruskals::getCellGroup(
	const Coordinates& cell)
{
	auto predicate = [&cell](const CellGroups::value_type& item) {
		return item.find(cell) != item.end();
	};

	return std::find_if(cellGroups.begin(), cellGroups.end(), predicate);
}

void RandomizedKruskals::createGroup(const Passage& cells)
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
