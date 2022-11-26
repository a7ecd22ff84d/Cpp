#include "Core/Mazes/RecursiveBacktrackingGenerator.h"

#include <algorithm>
#include <string_view>

#include "Core/Random/VariableRangeRng.h"

namespace Core::Mazes
{
void RecursiveBacktrackingGenerator::initNewMaze(
	std::size_t height, std::size_t width, const std::string& seed)
{
	this->seed = seed;

	bool createPassages = true;
	maze = Maze(height, width, createPassages);
	rng = VariableRangeRng(seed);

	stack = std::stack<Coordinates>();
	stack.push({0, 0});
}

auto RecursiveBacktrackingGenerator::getMaze() const -> const Maze&
{
	return maze;
}

auto RecursiveBacktrackingGenerator::step() -> bool
{
	auto currentCell = stack.top();
	auto adjacentCells = getAdjacentCells(currentCell);
	removeVisitedCells(adjacentCells);

	if (adjacentCells.empty())
	{
		setCellStatus(currentCell, Maze::CellValueType::Visited);
		stack.pop();

		if (stack.empty())
			return false;

		auto nextCell = stack.top();

		if (currentCell.column == nextCell.column)
		{
			maze.setSouthPassage(
				std::min(currentCell.row, nextCell.row),
				currentCell.column,
				Maze::EastPassageValueType::Visited);
		}
		else if (currentCell.row == nextCell.row)
		{
			maze.setEastPassage(
				currentCell.row,
				std::min(currentCell.column, nextCell.column),
				Maze::EastPassageValueType::Visited);
		}
	}
	else
	{
		auto nextCell = getNextCell(adjacentCells);

		stack.push(nextCell);
		setCellStatus(currentCell, Maze::CellValueType::InStack);

		if (currentCell.column == nextCell.column)
		{
			maze.setSouthPassage(
				std::min(currentCell.row, nextCell.row),
				currentCell.column,
				Maze::EastPassageValueType::InStack);
		}
		else if (currentCell.row == nextCell.row)
		{
			maze.setEastPassage(
				currentCell.row,
				std::min(currentCell.column, nextCell.column),
				Maze::EastPassageValueType::InStack);
		}
	}

	setCellStatus(stack.top(), Maze::CellValueType::Active);
	return true;
}

auto RecursiveBacktrackingGenerator::getAdjacentCells(Coordinates cell) const
	-> RecursiveBacktrackingGenerator::Cells
{
	Cells adjacentCells;

	if (cell.column > 0)
		adjacentCells.emplace_back(Coordinates{cell.column - 1, cell.row});
	if (cell.column < maze.width() - 1)
		adjacentCells.emplace_back(Coordinates{cell.column + 1, cell.row});
	if (cell.row > 0)
		adjacentCells.emplace_back(Coordinates{cell.column, cell.row - 1});
	if (cell.row < maze.height() - 1)
		adjacentCells.emplace_back(Coordinates{cell.column, cell.row + 1});

	return adjacentCells;
}

void RecursiveBacktrackingGenerator::removeVisitedCells(Cells& cells) const
{
	auto predicate = [=](const Coordinates& c) {
		return maze.cellValue(c.row, c.column) != Maze::CellValueType::NotVisited;
	};

	cells.erase(std::remove_if(cells.begin(), cells.end(), predicate), cells.end());
}

auto RecursiveBacktrackingGenerator::getNextCell(const Cells& availabeCells)
	-> Coordinates
{
	auto cellsCount = availabeCells.size();
	if (cellsCount == 1)
		return availabeCells.front();

	return availabeCells[rng.getRandom(0, cellsCount - 1)];
}

void RecursiveBacktrackingGenerator::setCellStatus(
	Coordinates coordinates, Maze::CellValueType status)
{
	maze.setCell(coordinates.row, coordinates.column, status);
}

} // namespace Core::Mazes
