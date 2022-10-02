#pragma once

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>

#include "Core/Grids/Grid.h"
#include "Core/SfmlTools/Sfml_fwd.h"

namespace Visualization
{
class GridPrinter
{
	static constexpr auto cellHeight = 10.0f;

public:
	void init(const Grids::Grid& grid);
	void print(sf::RenderWindow* renderWindows); // todo: renderwindow can be changed to rendertarget

private:
	void create(const Grids::Grid& grid);
	void update(const Grids::Grid& grid);

private:
	std::vector<std::vector<sf::RectangleShape>> cells;
};

} // namespace Visualization