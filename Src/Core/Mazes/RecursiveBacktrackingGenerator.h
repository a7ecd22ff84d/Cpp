#ifndef __MAZE_GENERATOR_H
#define __MAZE_GENERATOR_H

#include <stack>
#include <string_view>

#include "Core/Mazes/BaseGenerator.h"

namespace Mazes
{
class RecursiveBacktrackingGenerator : public BaseGenerator
{
	using Cells = std::vector<Coordinates>;

public:
	void initNewMaze(const GeneratorContext& context) final;
	bool step() final;

private:
	Cells getAdjacentCells(Coordinates coordinates) const;
	void removeVisitedCells(Cells& cells) const;
	Coordinates getNextCell(const Cells& availabeCells);
	void setCellStatus(Coordinates coordinates, CellStatus status);

private:
	std::stack<Coordinates> stack;
};

} // namespace Mazes

#endif //__MAZE_GENERATOR_H