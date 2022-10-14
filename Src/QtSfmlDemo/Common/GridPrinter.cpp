#include "QtSfmlDemo/Common/GridPrinter.h"

#include <QDebug>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace Visualization
{
void GridPrinter::init(const Grids::Grid& grid, const GridPrinterParams& params)
{
	create(grid, params);
	update(grid);
}

void GridPrinter::print(sf::RenderWindow* renderWindow)
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

auto GridPrinter::getGridArea() const -> sf::Vector2f
{
	return gridArea;
}

void GridPrinter::create(const Grids::Grid& grid, const GridPrinterParams& params)
{
	auto cellSize = static_cast<float>(params.cellSize);
	auto passageWidth = grid.hasPassages() ? params.passageWidth : 0.0f;

	gridArea = sf::Vector2f{
		grid.width() * (cellSize + passageWidth) - passageWidth,
		grid.height() * (cellSize + passageWidth) - passageWidth};

	cells.clear();
	eastPassages.clear();
	southPassages.clear();

	cells.resize(
		grid.height(), {grid.width(), sf::RectangleShape({cellSize, cellSize})});

	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			cells[i][j].setPosition(
				{j * (cellSize + passageWidth), i * (cellSize + passageWidth)});
		}
	}

	if (not grid.hasPassages())
		return;

	eastPassages.resize(
		grid.height(),
		{grid.width() - 1, sf::RectangleShape({passageWidth, cellSize})});

	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width() - 1; j++)
		{
			eastPassages[i][j].setPosition(
				{(j + 1) * (cellSize + passageWidth) - passageWidth,
				 i * (cellSize + passageWidth)});
		}
	}

	southPassages.resize(
		grid.height() - 1,
		{grid.width(), sf::RectangleShape({cellSize, passageWidth})});

	for (auto i = 0u; i < grid.height() - 1; i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			southPassages[i][j].setPosition(
				{j * (cellSize + passageWidth),
				 (i + 1) * (cellSize + passageWidth) - passageWidth});
		}
	}
}

void GridPrinter::update(const Grids::Grid& grid)
{
	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			if (grid.cellValue(i, j) == true)
				cells[i][j].setFillColor(sf::Color::White);
			else
				cells[i][j].setFillColor(sf::Color::Black);
		}
	}

	if (not grid.hasPassages())
		return;

	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width() - 1; j++)
		{
			if (grid.eastPassageValue(i, j) == true)
				eastPassages[i][j].setFillColor(sf::Color::Green);
			else
				eastPassages[i][j].setFillColor(sf::Color::Blue);
		}
	}

	for (auto i = 0u; i < grid.height() - 1; i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			if (grid.southPassageValue(i, j) == true)
				southPassages[i][j].setFillColor(sf::Color::Red);
			else
				southPassages[i][j].setFillColor(sf::Color::Yellow);
		}
	}
}

} // namespace Visualization