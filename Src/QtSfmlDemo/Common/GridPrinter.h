#pragma once

#include <cmath>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Core/Containers/EnumMapper.hpp"
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

enum class CellType
{
	None,
	Cell,
	EastPassage,
	SouthPassage,
	Vertex,
};

constexpr auto cellTypeMapper = Containers::EnumMapper<CellType, 5, 12>{
	{{{CellType::None, "None"},
	  {CellType::Cell, "Cell"},
	  {CellType::EastPassage, "EastPassage"},
	  {CellType::SouthPassage, "SouthPassage"},
	  {CellType::Vertex, "Vertex"}}}};

struct CellInfo
{
	sf::Vector2u coordinates;
	CellType type = CellType::None;
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

	void print(sf::RenderWindow& renderWindow) const
	{
		for (const auto& row : cells)
		{
			for (const auto& item : row)
			{
				renderWindow.draw(item);
			}
		}

		for (const auto& row : eastPassages)
		{
			for (const auto& item : row)
			{
				renderWindow.draw(item);
			}
		}

		for (const auto& row : southPassages)
		{
			for (const auto& item : row)
			{
				renderWindow.draw(item);
			}
		}
	}

	[[nodiscard]] auto getGridArea() const -> sf::Vector2f
	{
		return gridArea;
	}

	[[nodiscard]] auto getSelectedCell(sf::RenderWindow* renderWindow) const
		-> CellInfo
	{
		auto position = sf::Mouse::getPosition(*renderWindow);
		auto wordPosition = renderWindow->mapPixelToCoords(position);

		if (wordPosition.x < 0 || wordPosition.x > gridArea.x
			|| wordPosition.y < 0 || wordPosition.y > gridArea.y)
		{
			return {{0, 0}};
		}

		auto cpSize = cellSize + passageWidth;
		auto cellInfo = CellInfo{
			{static_cast<unsigned>(wordPosition.x / cpSize),
			 static_cast<unsigned>(wordPosition.y / cpSize)},
			CellType::Cell};

		if (std::abs(passageWidth) < 0.00001)
			return cellInfo;

		auto modX = wordPosition.x - cpSize * cellInfo.coordinates.x;
		auto modY = wordPosition.y - cpSize * cellInfo.coordinates.y;

		if (modX > cellSize && modY < cellSize)
			cellInfo.type = CellType::EastPassage;
		else if (modX < cellSize && modY > cellSize)
			cellInfo.type = CellType::SouthPassage;
		else if (modX > cellSize && modY > cellSize)
			cellInfo.type = CellType::Vertex;

		return cellInfo;
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
						spPainter(
							grid.southPassageValue(i, j), southPassages[i][j]);
				}
			}
		}
	}

private:
	void create(
		std::size_t height,
		std::size_t width,
		bool createPassages,
		const GridPrinterParams<GridT>& params)
	{
		cellSize = static_cast<float>(params.cellSize);
		passageWidth = createPassages ? params.passageWidth : 0.0f;
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

private:
	float cellSize;
	float passageWidth;

	std::vector<std::vector<sf::RectangleShape>> cells;
	std::vector<std::vector<sf::RectangleShape>> eastPassages;
	std::vector<std::vector<sf::RectangleShape>> southPassages;

	std::function<void(typename GridT::CellValueType, sf::RectangleShape& rect)> cellPainter;
	std::function<void(typename GridT::EastPassageValueType, sf::RectangleShape& rect)> epPainter;
	std::function<void(typename GridT::SouthPassageValueType, sf::RectangleShape& rect)> spPainter;

	sf::Vector2f gridArea;
}; // namespace Visualization

} // namespace Visualization