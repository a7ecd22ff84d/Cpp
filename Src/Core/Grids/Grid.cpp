#include "Core/Grids/Grid.h"

namespace Grids
{
Grid::Grid(std::size_t height, std::size_t width, bool createPassages)
	: cells(std::vector<Row>(height, Row(width, false)))
{
	if (createPassages)
	{
		eastPassages =
			std::vector(std::vector<Row>(height, Row(width - 1, false)));
		southPassages =
			std::vector(std::vector<Row>(height - 1, Row(width, false)));
	}
}

auto Grid::height() const -> std::size_t
{
	return cells.size();
}

auto Grid::width() const -> std::size_t
{
	return cells[0].size();
}

auto Grid::hasPassages() const -> bool
{
	return eastPassages.size() > 0 or southPassages.size() > 0;
}

void Grid::setCell(int x, int y, bool value)
{
	cells[x][y] = value;
}

void Grid::setEastPassage(int x, int y, bool value)
{
	eastPassages[x][y] = value;
}

void Grid::setSouthPassage(int x, int y, bool value)
{
	southPassages[x][y] = value;
}

auto Grid::cellValue(int x, int y) const -> bool
{
	return cells[x][y];
}

auto Grid::eastPassageValue(int x, int y) const -> bool
{
	return eastPassages[x][y];
}

auto Grid::southPassageValue(int x, int y) const -> bool
{
	return southPassages[x][y];
}

} // namespace Grids