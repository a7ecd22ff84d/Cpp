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
	stack.push({22, 28});
	visitedCells[22][28] = true;
}

void MazeGenerator::step()
{
	auto currentCell = stack.top();
	printCells("Current cell", {currentCell});

	auto adjacentCells = getAdjacentCells(currentCell);
	printCells("Adjacent cells", adjacentCells);

	removeVisitedCells(adjacentCells);
	printCells("Adjacent not empty cells", adjacentCells);

	auto nextCell = adjacentCells[rand() % adjacentCells.size()];
	printCells("Next cell", {nextCell});

	stack.push(nextCell);
	visitedCells[nextCell.row][nextCell.column] = true;
	maze.push_back({currentCell, nextCell});
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
		return visitedCells[c.row][c.column];
	};

	cells.erase(std::remove_if(cells.begin(), cells.end(), predicate), cells.end());
}
