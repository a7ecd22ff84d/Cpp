#pragma once

#include <vector>

namespace Grids
{
template<typename CV, typename EPV, typename SPV>
class Grid
{
	using Row = std::vector<CV>;

public:
	using CellValueType = CV;
	using EastPassageValueType = EPV;
	using SouthPassageValueType = SPV;

	Grid() = default;
	Grid(std::size_t height, std::size_t width, bool createPassages)
		: cells(std::vector<Row>(height, Row(width, CV())))
	{
		if (createPassages)
		{
			eastPassages =
				std::vector(std::vector<Row>(height, Row(width - 1, false)));
			southPassages =
				std::vector(std::vector<Row>(height - 1, Row(width, false)));
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
	[[nodiscard]] auto eastPassageValue(int x, int y) const -> bool
	{
		return eastPassages[x][y];
	}
	[[nodiscard]] auto southPassageValue(int x, int y) const -> bool
	{
		return southPassages[x][y];
	}

private:
	std::vector<std::vector<CV>> cells;
	std::vector<std::vector<EPV>> eastPassages;
	std::vector<std::vector<SPV>> southPassages;
};

} // namespace Grids