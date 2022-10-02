#include "Core/Grids/Grid.h"



namespace Grids
{
Grid::Grid(std::size_t height, std::size_t width)
	: cells(std::vector<Row>(height, Row(width, false)))
{
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