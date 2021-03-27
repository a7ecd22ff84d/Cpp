#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeGenerator.h"

#include <algorithm>
#include <string_view>

#include "Core/Random/VariableRangeRng.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

MazeGenerator::MazeGenerator()
{
}

void MazeGenerator::initNewMaze(const GeneratorContext& context)
{
	rng = VariableRangeRng(context.seed);

	maze = Maze();
	maze.width = context.width;
	maze.height = context.height;

	maze.cellStatuses = std::vector<std::vector<CellStatus>>(
		context.height,
		std::vector<CellStatus>(context.width, CellStatus::notVisited));

	stack = std::stack<Coordinates>();
	stack.push({0, 0});
}

bool MazeGenerator::step()
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

const Maze& MazeGenerator::getMaze() const
{
	return maze;
}

std::vector<Coordinates> MazeGenerator::getAdjacentCells(Coordinates cell) const
{
	std::vector<Coordinates> adjacentCells;

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

void MazeGenerator::removeVisitedCells(Cells& cells) const
{
	auto predicate = [=](const Coordinates& c) {
		return maze.cellStatuses[c.row][c.column] != CellStatus::notVisited;
	};

	cells.erase(std::remove_if(cells.begin(), cells.end(), predicate), cells.end());
}

Coordinates MazeGenerator::getNextCell(const Cells& availabeCells)
{
	auto cellsCount = availabeCells.size();
	if (cellsCount == 1)
		return availabeCells[0];

	return availabeCells[rng.getRandom(0, cellsCount - 1)];
}

void MazeGenerator::setCellStatus(Coordinates coordinates, CellStatus status)
{
	maze.cellStatuses[coordinates.row][coordinates.column] = status;
}