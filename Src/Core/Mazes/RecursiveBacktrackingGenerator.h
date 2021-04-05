#ifndef __MAZE_GENERATOR_H
#define __MAZE_GENERATOR_H

#include <stack>
#include <string_view>

#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Random/VariableRangeRng.h"

using Cells = std::vector<Coordinates>;

class RecursiveBacktrackingGenerator : public IMazeGenerator
{
public:
	void initNewMaze(const GeneratorContext& context) final;
	bool step() final;
	const Maze& getMaze() const final;

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