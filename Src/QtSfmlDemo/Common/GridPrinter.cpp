#include "QtSfmlDemo/Common/GridPrinter.h"

#include <QDebug>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
}

void GridPrinter::create(const Grids::Grid& grid)
{
	cells.clear();

	cells.resize(
		grid.height(),
		{grid.width(), sf::RectangleShape({cellHeight, cellHeight})});

	for (auto i = 0u; i < grid.height(); i++)
	{
		for (auto j = 0u; j < grid.width(); j++)
		{
			cells[i][j].setPosition({j * cellHeight, i * cellHeight});
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
}

} // namespace Visualization