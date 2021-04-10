#ifndef __RANDOMIZED_KRUSKALS
#define __RANDOMIZED_KRUSKALS

#include <list>
#include <optional>
#include <set>

#include "Core/Mazes/BaseGenerator.h"
#include "Core/Mazes/Maze.h"

namespace Mazes
{
class RandomizedKruskals : public BaseGenerator
{
	using CellGroup = std::set<Coordinates>;
	using CellGroups = std::vector<CellGroup>;

public:
	void initNewMaze(const GeneratorContext& context) final;
	bool step() final;

private:
	void addCellEdges(unsigned row, unsigned column);
	const Passage& getRandomEdge();
	void setCellStatus(const Coordinates& cell, CellStatus status);

	void handleCellGroups(const Passage& edge);
	CellGroups::iterator getCellGroup(const Coordinates& cell);
	void createGroup(const Passage& cells);
	void mergeGroups(CellGroup& first, CellGroup& second);
	void removeRedundantEdges(const CellGroup& group);

private:
	std::optional<Passage> previousPassage;
	std::list<Passage> edges;
	CellGroups cellGroups;
};

} // namespace Mazes

#endif
