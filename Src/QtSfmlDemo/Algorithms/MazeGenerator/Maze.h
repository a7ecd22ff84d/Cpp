#ifndef __MAZE_H
#define __MAZE_H

#include <utility>
#include <vector>

struct Coordinates
{
	int row;
	int column;
};

using Passage = std::pair<Coordinates, Coordinates>;
using Maze = std::vector<Passage>;

#endif