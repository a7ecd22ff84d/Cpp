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
public:
	template<typename GridT>
	void init(const GridT& grid, const GridPrinterParams& params)
	{
		create(grid.height(), grid.width(), grid.hasPassages(), params);
		update(grid);
	}

	void print(sf::RenderWindow* renderWindows);

	[[nodiscard]] auto getGridArea() const -> sf::Vector2f;

private:
	void create(
		std::size_t height,
		std::size_t width,
		bool createPassages,
		const GridPrinterParams& params);

	template<typename GridT>
	void update(const GridT& grid)
	{
		auto cellPainter = [](typename GridT::CellValueType value,
							  sf::RectangleShape& rect) {
			rect.setFillColor(value ? sf::Color::White : sf::Color::Black);
		};

		auto epPainter = [](bool value, sf::RectangleShape& rect) {
			rect.setFillColor(value ? sf::Color::Green : sf::Color::Blue);
		};

		auto spPainter = [](bool value, sf::RectangleShape& rect) {
			rect.setFillColor(value ? sf::Color::Red : sf::Color::Yellow);
		};

		for (auto i = 0u; i < grid.height(); i++)
		{
			for (auto j = 0u; j < grid.width(); j++)
			{
				cellPainter(grid.cellValue(i, j), cells[i][j]);

				if (grid.hasPassages())
				{
					if (j < grid.width() - 1)
						epPainter(grid.eastPassageValue(i, j), eastPassages[i][j]);

					if (i < grid.height() - 1)
						spPainter(grid.eastPassageValue(i, j), southPassages[i][j]);
				}
			}
		}
	}

private:
	std::vector<std::vector<sf::RectangleShape>> cells;
	std::vector<std::vector<sf::RectangleShape>> eastPassages;
	std::vector<std::vector<sf::RectangleShape>> southPassages;
	sf::Vector2f gridArea;
}; // namespace Visualization

} // namespace Visualization