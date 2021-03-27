#ifndef __MAZE_GENERATOR_H
#define __MAZE_GENERATOR_H

#include <stack>
#include <string_view>

#include "Core/Random/VariableRangeRng.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

using Cells = std::vector<Coordinates>;

struct GeneratorContext
{
	int width;
	int height;
	std::string_view seed;
};

class MazeGenerator
{
public:
	MazeGenerator();

	void initNewMaze(const GeneratorContext& context);
	bool step();
	const Maze& getMaze() const;

private:
	Cells getAdjacentCells(Coordinates coordinates) const;
	void removeVisitedCells(Cells& cells) const;
	Coordinates getNextCell(const Cells& availabeCells);
	void setCellStatus(Coordinates coordinates, CellStatus status);

private:
	Maze maze;
	std::stack<Coordinates> stack;
	VariableRangeRng rng;
};

#endif //__MAZE_GENERATOR_H