#ifndef __MAZE_H
#define __MAZE_H

#include <array>
#include <utility>
#include <vector>

enum class CellStatus
{
	notVisited,
	visited,
	inStack,
	active,
};

struct Coordinates
{
	int row;
	int column;
};

using Passage = std::pair<Coordinates, Coordinates>;

struct Maze
{
	std::vector<Passage> passages;
	std::array<std::array<CellStatus, 30>, 24> cellStatuses;
};

#endif