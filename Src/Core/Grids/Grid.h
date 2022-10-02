#pragma once

#include <vector>

// todo: add passage support

namespace Grids
{
class Grid
{
	using Row = std::vector<bool>;

public:
	Grid(std::size_t height, std::size_t width/*, bool createPassages*/);

	[[nodiscard]] auto height() const  -> std::size_t;
	[[nodiscard]] auto width() const -> std::size_t;

// private:
	std::vector<std::vector<bool>> cells;
	// std::vector<std::vector<bool>> rightPassages;
	// std::vector<std::vector<bool>> leftPassages;
};

} // namespace Grids