#pragma once

#include <vector>

namespace Grids
{
class Grid
{
	using Row = std::vector<bool>;

public:
	Grid() = default;
	Grid(std::size_t height, std::size_t width, bool createPassages);

	[[nodiscard]] auto height() const -> std::size_t;
	[[nodiscard]] auto width() const -> std::size_t;
	[[nodiscard]] auto hasPassages() const -> bool;

	std::vector<std::vector<bool>> cells;
	std::vector<std::vector<bool>> eastPassages;
	std::vector<std::vector<bool>> southPassages;
};

} // namespace Grids