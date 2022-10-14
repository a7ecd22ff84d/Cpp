#include "QtSfmlDemo/Common/GridPrinter.h"

#include <QDebug>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace Visualization
{
void GridPrinter::init(const Grids::Grid& grid)
{
	create(grid);
	update(grid);
}

void GridPrinter::print(sf::RenderWindow* renderWindow)
{
	auto test = sf::RectangleShape({cellHeight, cellHeight});
	test.setFillColor(sf::Color::Red);
	renderWindow->draw(test);

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

void GridPrinter::create(const Grids::Grid& grid)
{
	auto passageWidth = grid.hasPassages() ? 2.0f : 0.0f;

	gridArea = sf::Vector2f{
		grid.width() * (cellHeight + passageWidth) - passageWidth,
		grid.height() * (cellHeight + passageWidth) - passageWidth};

	cells.clear();
	eastPassages.clear();
	southPassages.clear();

	cells.resize(
		grid.height(),
		{grid.width(), sf::RectangleShape({cellHeight, cellHeight})});

	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			cells[i][j].setPosition(
				{j * (cellHeight + passageWidth), i * (cellHeight + passageWidth)});
		}
	}

	if (not grid.hasPassages())
		return;

	eastPassages.resize(
		grid.height(),
		{grid.width() - 1, sf::RectangleShape({passageWidth, cellHeight})});

	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width() - 1; j++)
		{
			eastPassages[i][j].setPosition(
				{(j + 1) * (cellHeight + passageWidth) - passageWidth,
				 i * (cellHeight + passageWidth)});
		}
	}

	southPassages.resize(
		grid.height() - 1,
		{grid.width(), sf::RectangleShape({cellHeight, passageWidth})});

	for (auto i = 0u; i < grid.height() - 1; i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			southPassages[i][j].setPosition(
				{j * (cellHeight + passageWidth),
				 (i + 1) * (cellHeight + passageWidth) - passageWidth});
		}
	}
}

void GridPrinter::update(const Grids::Grid& grid)
{
	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			if (grid.cells[i][j] == true)
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
			if (grid.cells[i][j] == true)
				eastPassages[i][j].setFillColor(sf::Color::Green);
			else
				eastPassages[i][j].setFillColor(sf::Color::Blue);
		}
	}

	for (auto i = 0u; i < grid.height() - 1; i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			if (grid.cells[i][j] == true)
				southPassages[i][j].setFillColor(sf::Color::Red);
			else
				southPassages[i][j].setFillColor(sf::Color::Yellow);
		}
	}
}

} // namespace Visualization