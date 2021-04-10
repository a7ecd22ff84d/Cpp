#ifndef __I_MAZE_GENERATOR_H
#define __I_MAZE_GENERATOR_H

#include <string>
#include <string_view>

#include "Core/Mazes/Maze.h"

namespace Mazes
{
struct GeneratorContext
{
	unsigned width;
	unsigned height;
	std::string seed;
};

class IMazeGenerator
{
public:
	virtual ~IMazeGenerator()
	{
	}

	virtual void initNewMaze(const GeneratorContext& context) = 0;
	virtual bool step() = 0;
	virtual const Maze& getMaze() const = 0;
};

} // namespace Mazes

#endif