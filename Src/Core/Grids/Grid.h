#pragma once

#include <bits/c++config.h>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace Grids
{
struct Coordinates
{
	unsigned column;
	unsigned row;
};

enum class PassageType
{
	East,
	South,
};

struct Passage
{
	Passage(Coordinates first, Coordinates second)
		: first(first)
		, second(second)
	{
		if (std::abs(static_cast<int>(first.column) - static_cast<int>(second.column))
				> 1
			or std::abs(static_cast<int>(first.row) - static_cast<int>(second.row))
				> 1)
		{
			std::logic_error("Passage can be created only between adjacent cells");
		}
	}

	[[nodiscard]] auto type() const -> PassageType
	{
		if (first.row == second.row)
			return PassageType::East;
		else
			return PassageType::South;
	}

	Coordinates first;
	Coordinates second;
};

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

	void setCell(Coordinates c, CV value)
	{
		cells[c.row][c.column] = value;
	}
	void setEastPassage(Coordinates c, EPV value)
	{
		eastPassages[c.row][c.column] = value;
	}
	void setSouthPassage(Coordinates c, SPV value)
	{
		southPassages[c.row][c.column] = value;
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

	[[nodiscard]] auto cellValue(Coordinates c) const -> CV
	{
		return cells[c.row][c.column];
	}
	[[nodiscard]] auto eastPassageValue(Coordinates c) const -> EPV
	{
		return eastPassages[c.row][c.column];
	}
	[[nodiscard]] auto southPassageValue(Coordinates c) const -> SPV
	{
		return southPassages[c.row][c.column];
	}

	void setEastPassage(Passage p, EPV value)
	{
		if (p.type() == PassageType::East)
			std::logic_error("Wrong passage type");

		eastPassages[std::min(p.first.row, p.second.row)]
					[std::min(p.first.column, p.second.column)] = value;
	}
	void setSouthPassage(Passage p, SPV value)
	{
		if (p.type() == PassageType::South)
			std::logic_error("Wrong passage type");

		southPassages[std::min(p.first.row, p.second.row)]
					 [std::min(p.first.column, p.second.column)] = value;
	}

	[[nodiscard]] auto eastPassageValue(Passage p) const -> EPV
	{
		if (p.type() == PassageType::East)
			std::logic_error("Wrong passage type");

		return eastPassages[std::min(p.first.row, p.second.row)]
						   [std::min(p.first.column, p.second.column)];
	}
	[[nodiscard]] auto southPassageValue(Passage p) const -> SPV
	{
		if (p.type() == PassageType::South)
			std::logic_error("Wrong passage type");

		return southPassages[std::min(p.first.row, p.second.row)]
							[std::min(p.first.column, p.second.column)];
	}

private:
	std::vector<std::vector<CV>> cells;
	std::vector<std::vector<EPV>> eastPassages;
	std::vector<std::vector<SPV>> southPassages;
};

} // namespace Grids