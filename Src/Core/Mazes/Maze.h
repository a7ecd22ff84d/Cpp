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
	Coordinates(unsigned row, unsigned column) : row(row), column(column)
	{
	}

	bool operator<(const Coordinates& other) const
	{
		if (row == other.row)
			return column < other.column;
		else
			return row < other.row;
	}

	unsigned row;
	unsigned column;
};

using Passage = std::pair<Coordinates, Coordinates>;

struct Maze
{
	unsigned width;
	unsigned height;

	std::vector<Passage> passages;
	std::vector<std::vector<CellStatus>> cellStatuses;
};

#endif