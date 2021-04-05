#ifndef __RANDOMIZED_KRUSKALS
#define __RANDOMIZED_KRUSKALS

#include <list>
#include <set>

#include "Core/Generator/Maze/IMazeGenerator.h"
#include "Core/Generator/Maze/Maze.h"
#include "Core/Random/VariableRangeRng.h"

namespace Mazes
{
class RandomizedKruskals : public IMazeGenerator
{
	using Edge = std::pair<Coordinates, Coordinates>;
	using CellGroups=std::vector<std::set<Coordinates>>;

public:
	void initNewMaze(const GeneratorContext& context) final;
	bool step() final;
	const Maze& getMaze() const final;

private:
	void addCellEdges(unsigned row, unsigned column);
	std::set<Edge>::iterator getRandomEdge();
	void setCellStatus(Coordinates cell, CellStatus status);

	CellGroups::iterator getCellGroup(Coordinates cell);
	void createGroup(Passage cells);
	void mergeGroups(CellGroups::iterator first, CellGroups::iterator second);	

private:
	Passage previousPassage = std::make_pair(Coordinates{0,0}, Coordinates{0,0});
	Maze maze;
	VariableRangeRng rng;
	std::set<Edge> edges;
	CellGroups cellGroups;
};

} // namespace Mazes

#endif
