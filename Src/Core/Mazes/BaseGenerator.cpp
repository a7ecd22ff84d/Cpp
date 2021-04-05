#include "Core/Mazes/BaseGenerator.h"

namespace Mazes
{
void BaseGenerator::initNewMaze(const GeneratorContext& context)
{
	rng = VariableRangeRng(context.seed);

	maze = Maze();
	maze.width = context.width;
	maze.height = context.height;

	maze.cellStatuses = std::vector<std::vector<CellStatus>>(
		context.height,
		std::vector<CellStatus>(context.width, CellStatus::notVisited));
}

const Maze& BaseGenerator::getMaze() const
{
	return maze;
}

} // namespace Mazes