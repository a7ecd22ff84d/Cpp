#ifndef __RANDOMIZED_KRUSKALS
#define __RANDOMIZED_KRUSKALS

#include <list>
#include <optional>
#include <set>

#include "Core/Mazes/BaseGenerator.h"

namespace Mazes
{
class RandomizedKruskals : public BaseGenerator
{
	using CellGroups = std::vector<std::set<Coordinates>>;

public:
	void initNewMaze(const GeneratorContext& context) final;
	bool step() final;

private:
	void addCellEdges(unsigned row, unsigned column);
	std::set<Passage>::iterator getRandomEdge();
	void setCellStatus(const Coordinates& cell, CellStatus status);

	void handleCellGroups(std::set<Passage>::iterator edge);
	CellGroups::iterator getCellGroup(const Coordinates& cell);
	void createGroup(const Passage& cells);
	void mergeGroups(CellGroups::iterator first, CellGroups::iterator second);

private:
	std::optional<Passage> previousPassage;
	std::set<Passage> edges;
	CellGroups cellGroups;
};

} // namespace Mazes

#endif
