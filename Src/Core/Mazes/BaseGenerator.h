#ifndef __BASE_GENERATOR_H
#define __BASE_GENERATOR_H

#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Random/VariableRangeRng.h"

namespace Mazes
{
class BaseGenerator : public IMazeGenerator
{
public:
	virtual void initNewMaze(const GeneratorContext& context) override;
	virtual const Maze& getMaze() const final;

protected:
	Maze maze;
	VariableRangeRng rng;
};

} // namespace Mazes

#endif