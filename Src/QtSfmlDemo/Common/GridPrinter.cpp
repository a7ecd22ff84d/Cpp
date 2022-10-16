#include "QtSfmlDemo/Common/GridPrinter.h"

#include <QDebug>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace Visualization
{
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

void GridPrinter::create(
	std::size_t height,
	std::size_t width,
	bool createPassages,
	const GridPrinterParams& params)
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

} // namespace Visualization