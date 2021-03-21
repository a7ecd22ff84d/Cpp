#ifndef __MAZE_H
#define __MAZE_H

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
	int width;
	int height;

	std::vector<Passage> passages;
	std::vector<std::vector<CellStatus>> cellStatuses;};

#endif