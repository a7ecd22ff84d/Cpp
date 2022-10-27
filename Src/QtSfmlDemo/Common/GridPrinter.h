#pragma once

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Core/Grids/Grid.h"
#include "Core/SfmlTools/Sfml_fwd.h"

namespace Visualization
{
template<typename GridT>
struct GridPrinterParams
{
	std::size_t cellSize;
	std::size_t passageWidth;

	std::function<void(typename GridT::CellValueType, sf::RectangleShape& rect)> cellPainter;
	std::function<void(typename GridT::EastPassageValueType, sf::RectangleShape& rect)> epPainter;
	std::function<void(typename GridT::SouthPassageValueType, sf::RectangleShape& rect)> spPainter;
};

template<typename GridT>
class GridPrinter
{
public:
	void init(const GridT& grid, const GridPrinterParams<GridT>& params)
	{
		cellPainter = params.cellPainter;
		epPainter = params.epPainter;
		spPainter = params.spPainter;

		create(grid.height(), grid.width(), grid.hasPassages(), params);
		update(grid);
	}

	void print(sf::RenderWindow* renderWindow)
	{
		for (const auto& row : cells)
		{
			for (const auto& item : row)
			{
				renderWindow->draw(item);
			}
		}

		for (const auto& row : eastPassages)
		{
			for (const auto& item : row)
			{
				renderWindow->draw(item);
			}
		}

		for (const auto& row : southPassages)
		{
			for (const auto& item : row)
			{
				renderWindow->draw(item);
			}
		}
	}

	[[nodiscard]] auto getGridArea() const -> sf::Vector2f
	{
		return gridArea;
	}

private:
	void create(
		std::size_t height,
		std::size_t width,
		bool createPassages,
		const GridPrinterParams<GridT>& params)
	{
		auto cellSize = static_cast<float>(params.cellSize);
		auto passageWidth = createPassages ? params.passageWidth : 0.0f;
		auto cpSize = cellSize + passageWidth;

		gridArea = sf::Vector2f{
			width * cpSize - passageWidth, height * cpSize - passageWidth};

		cells.clear();
		eastPassages.clear();
		southPassages.clear();

		auto cell = sf::RectangleShape({cellSize, cellSize});
		cells.resize(height, {width, cell});

		if (createPassages)
		{
			auto eastPassage = sf::RectangleShape({passageWidth, cellSize});
			eastPassages.resize(height, {width - 1, eastPassage});

			auto southPassage = sf::RectangleShape({cellSize, passageWidth});
			southPassages.resize(height - 1, {width, southPassage});
		}

		for (auto i = 0u; i < height; i++)
		{
			for (auto j = 0u; j < width; j++)
			{
				cells[i][j].setPosition({j * cpSize, i * cpSize});

				if (createPassages)
				{
					if (j < width - 1)
					{
						eastPassages[i][j].setPosition(
							{j * cpSize + cellSize, i * cpSize});
					}

					if (i < height - 1)
					{
						southPassages[i][j].setPosition(
							{j * cpSize, i * cpSize + cellSize});
					}
				}
			}
		}
	}

	void update(const GridT& grid)
	{
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

	std::function<void(typename GridT::CellValueType, sf::RectangleShape& rect)> cellPainter;
	std::function<void(typename GridT::EastPassageValueType, sf::RectangleShape& rect)> epPainter;
	std::function<void(typename GridT::SouthPassageValueType, sf::RectangleShape& rect)> spPainter;

	sf::Vector2f gridArea;
}; // namespace Visualization

} // namespace Visualization