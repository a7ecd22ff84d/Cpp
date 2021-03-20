#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeGenerator.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string_view>

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

void printCells(std::string_view header, const Cells& cells)
{
	std::cout << header << std::endl;
	for (const auto& cell : cells)
	{
		std::cout << cell.row << ", " << cell.column << std::endl;
	}
}

MazeGenerator::MazeGenerator()
{
	stack.push({0, 0});
	visitedCells[0][0] = true;
}

void MazeGenerator::step()
{
	auto currentCell = stack.top();
	printCells("Current cell", {currentCell});

	auto adjacentCells = getAdjacentCells(currentCell);
	printCells("Adjacent cells", adjacentCells);

	removeVisitedCells(adjacentCells);
	printCells("Adjacent not empty cells", adjacentCells);

	if (adjacentCells.empty())
	{
		setCellStatus(currentCell, CellStatus::visited);
		stack.pop();
	}
	else
	{
		auto nextCell = adjacentCells[rand() % adjacentCells.size()];
		printCells("Next cell", {nextCell});

		stack.push(nextCell);
		maze.passages.push_back({currentCell, nextCell});
		setCellStatus(currentCell, CellStatus::inStack);
	}

	setCellStatus(stack.top(), CellStatus::active);
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