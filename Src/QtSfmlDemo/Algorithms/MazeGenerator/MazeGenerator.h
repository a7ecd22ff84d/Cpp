#ifndef __MAZE_GENERATOR_H
#define __MAZE_GENERATOR_H

#include <array>
#include <stack>

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

using Cells = std::vector<Coordinates>;

class MazeGenerator
{
public:
	MazeGenerator();

	void initNewMaze(int width, int height);
	bool step();
	const Maze& getMaze() const;
	void reset();

private:
	Cells getAdjacentCells(Coordinates coordinates) const;
	void removeVisitedCells(Cells& cells) const;
	void setCellStatus(Coordinates coordinates, CellStatus status);

private:
	Maze maze;
	std::stack<Coordinates> stack;
};

#endif //__MAZE_GENERATOR_H