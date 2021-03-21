#ifndef __MAZE_GENERATOR_H
#define __MAZE_GENERATOR_H

#include <array>
#include <stack>

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

const int columnsCount = 30;
const int rowsCount = 24;

using Cells = std::vector<Coordinates>;

class MazeGenerator
{
	using VisitedCells = std::array<std::array<bool, columnsCount>, rowsCount>;

public:
	MazeGenerator();

	bool step();
	const Maze& getMaze() const;

private:
	Cells getAdjacentCells(Coordinates coordinates) const;
	void removeVisitedCells(Cells& cells) const;
	void setCellStatus(Coordinates coordinates, CellStatus status);

private:
	Maze maze;
	std::stack<Coordinates> stack;
};

#endif //__MAZE_GENERATOR_H