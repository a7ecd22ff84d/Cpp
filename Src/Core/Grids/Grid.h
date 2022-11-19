#pragma once

#include <bits/c++config.h>
#include <vector>

#include "Core/Mazes/Maze.h"

namespace Grids
{
template<typename CV, typename EPV, typename SPV>
class Grid
{
public:
	using CellValueType = CV;
	using EastPassageValueType = EPV;
	using SouthPassageValueType = SPV;

	Grid() = default;
	Grid(std::size_t height, std::size_t width, bool createPassages)
		: cells(std::vector<std::vector<CV>>(height, std::vector<CV>(width, CV())))
	{
		if (createPassages)
		{
			eastPassages = std::vector<std::vector<EPV>>(
				height, std::vector<EPV>(width - 1, EPV{}));
			southPassages = std::vector<std::vector<SPV>>(
				height - 1, std::vector<SPV>(width, SPV{}));
		}
	}

	[[nodiscard]] auto height() const -> std::size_t
	{
		return cells.size();
	}
	[[nodiscard]] auto width() const -> std::size_t
	{
		return cells[0].size();
	}
	[[nodiscard]] auto hasPassages() const -> bool
	{
		return eastPassages.size() > 0 or southPassages.size() > 0;
	}

	void setCell(int x, int y, CV value)
	{
		cells[x][y] = value;
	}
	void setEastPassage(int x, int y, EPV value)
	{
		eastPassages[x][y] = value;
	}
	void setSouthPassage(int x, int y, SPV value)
	{
		southPassages[x][y] = value;
	}

	[[nodiscard]] auto cellValue(int x, int y) const -> CV
	{
		return cells[x][y];
	}
	[[nodiscard]] auto eastPassageValue(int x, int y) const -> EPV
	{
		return eastPassages[x][y];
	}
	[[nodiscard]] auto southPassageValue(int x, int y) const -> SPV
	{
		return southPassages[x][y];
	}

private:
	std::vector<std::vector<CV>> cells;
	std::vector<std::vector<EPV>> eastPassages;
	std::vector<std::vector<SPV>> southPassages;
};

} // namespace Grids