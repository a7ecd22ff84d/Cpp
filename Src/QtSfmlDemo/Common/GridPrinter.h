#pragma once

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Core/Grids/Grid.h"
#include "Core/SfmlTools/Sfml_fwd.h"

namespace Visualization
{
struct GridPrinterParams
{
	std::size_t cellSize;
	std::size_t passageWidth;
};

class GridPrinter
{
	// static constexpr auto cellHeight = 10.0f;

public:
	void init(const Grids::Grid& grid, const GridPrinterParams& params);
	void print(sf::RenderWindow* renderWindows);

	[[nodiscard]] auto getGridArea() const -> sf::Vector2f;

private:
	void create(const Grids::Grid& grid, const GridPrinterParams& params);
	void update(const Grids::Grid& grid);

private:
	std::vector<std::vector<sf::RectangleShape>> cells;
	std::vector<std::vector<sf::RectangleShape>> eastPassages;
	std::vector<std::vector<sf::RectangleShape>> southPassages;
	sf::Vector2f gridArea;
};

} // namespace Visualization