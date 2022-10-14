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

} // namespace Grids