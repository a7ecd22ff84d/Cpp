#include "Core/Mazes/RecursiveBacktrackingGenerator.h"

#include <algorithm>
#include <string_view>

#include "Core/Mazes/BaseGenerator.h"
#include "Core/Random/VariableRangeRng.h"

namespace Mazes
{
void RecursiveBacktrackingGenerator::initNewMaze(const GeneratorContext& context)
{
	BaseGenerator::initNewMaze(context);

	stack = std::stack<Coordinates>();
	stack.push({0, 0});
}

bool RecursiveBacktrackingGenerator::step()
{
	auto currentCell = stack.top();
	auto adjacentCells = getAdjacentCells(currentCell);
	removeVisitedCells(adjacentCells);

	if (adjacentCells.empty())
	{
		setCellStatus(currentCell, CellStatus::visited);
		stack.pop();

		if (stack.empty())
			return false;
	}
	else
	{
		auto nextCell = getNextCell(adjacentCells);

		stack.push(nextCell);
		maze.passages.push_back({currentCell, nextCell});
		setCellStatus(currentCell, CellStatus::inStack);
	}

	setCellStatus(stack.top(), CellStatus::active);
	return true;
}

RecursiveBacktrackingGenerator::Cells RecursiveBacktrackingGenerator::getAdjacentCells(
	Coordinates cell) const
{
	Cells adjacentCells;

	if (cell.column > 0)
		adjacentCells.emplace_back(Coordinates{cell.row, cell.column - 1});
	if (cell.column < maze.width - 1)
		adjacentCells.emplace_back(Coordinates{cell.row, cell.column + 1});
	if (cell.row > 0)
		adjacentCells.emplace_back(Coordinates{cell.row - 1, cell.column});
	if (cell.row < maze.height - 1)
		adjacentCells.emplace_back(Coordinates{cell.row + 1, cell.column});

	return adjacentCells;
}

void RecursiveBacktrackingGenerator::removeVisitedCells(Cells& cells) const
{
	auto predicate = [=](const Coordinates& c) {
		return maze.cellStatuses[c.row][c.column] != CellStatus::notVisited;
	};

	cells.erase(std::remove_if(cells.begin(), cells.end(), predicate), cells.end());
}

Coordinates RecursiveBacktrackingGenerator::getNextCell(const Cells& availabeCells)
{
	auto cellsCount = availabeCells.size();
	if (cellsCount == 1)
		return availabeCells[0];

	return availabeCells[rng.getRandom(0, cellsCount - 1)];
}

void RecursiveBacktrackingGenerator::setCellStatus(
	Coordinates coordinates, CellStatus status)
{
	maze.cellStatuses[coordinates.row][coordinates.column] = status;
}

} // namespace Mazes
