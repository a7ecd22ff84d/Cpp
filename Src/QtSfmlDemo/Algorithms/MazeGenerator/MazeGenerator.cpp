#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeGenerator.h"

#include <algorithm>

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

MazeGenerator::MazeGenerator()
{
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
		auto nextCell = adjacentCells[rand() % adjacentCells.size()];

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

void MazeGenerator::reset()
{
	maze = Maze();
	stack = std::stack<Coordinates>();
	stack.push({0, 0});
}

std::vector<Coordinates> MazeGenerator::getAdjacentCells(Coordinates cell) const
{
	std::vector<Coordinates> adjacentCells;

	if (cell.column > 0)
		adjacentCells.emplace_back(Coordinates{cell.row, cell.column - 1});
	if (cell.column < columnsCount - 1)
		adjacentCells.emplace_back(Coordinates{cell.row, cell.column + 1});
	if (cell.row > 0)
		adjacentCells.emplace_back(Coordinates{cell.row - 1, cell.column});
	if (cell.row < rowsCount - 1)
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

void MazeGenerator::setCellStatus(Coordinates coordinates, CellStatus status)
{
	maze.cellStatuses[coordinates.row][coordinates.column] = status;
}