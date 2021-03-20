#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

const int wallThickness = 2;
const int cellSize = 20;
const int roomSize = cellSize - 2 * wallThickness;

MazeCell::MazeCell(int row, int column)
{
	room = sf::RectangleShape({roomSize, roomSize});
	room.setPosition(
		column * cellSize + wallThickness, row * cellSize + wallThickness);
	room.setFillColor(sf::Color::Cyan);

	eastPassage = sf::RectangleShape({wallThickness * 2, roomSize});
	eastPassage.setPosition(
		{room.getPosition().x + roomSize, room.getPosition().y});
	eastPassage.setFillColor(sf::Color::Cyan);

	southPassage = sf::RectangleShape({roomSize, wallThickness * 2});
	southPassage.setPosition(
		{room.getPosition().x, room.getPosition().y + roomSize});
	southPassage.setFillColor(sf::Color::Cyan);
}

void MazeCell::draw(QtSfmlCanvas* canvas)
{
	canvas->draw(room);
	canvas->draw(eastPassage);
	canvas->draw(southPassage);
}

MazePrinter::MazePrinter(QtSfmlCanvas* canvas)
	: canvas(canvas)
	, border({600 - wallThickness * 2, 480 - wallThickness * 2})
{
	border.setPosition({wallThickness,wallThickness});
	border.setOutlineThickness(wallThickness);
	border.setOutlineColor(sf::Color::Red);
	border.setFillColor(sf::Color::Transparent);

	init();
}

void MazePrinter::init()
{
	for (int row = 0; row < 24; row++)
	{
		for (int column = 0; column < 30; column++)
		{
			mazeGrid[row][column] = MazeCell(row, column);
		}
	}
}

void MazePrinter::draw()
{
	canvas->clear();
	for (int row = 0; row < 24; row++)
	{
		for (int column = 0; column < 30; column++)
		{
			mazeGrid[row][column].draw(canvas);
		}
	}
	canvas->draw(border);
	canvas->display();
}