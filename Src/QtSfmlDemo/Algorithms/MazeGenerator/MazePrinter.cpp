#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

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
	eastPassage.setFillColor(sf::Color::Black);

	southPassage = sf::RectangleShape({roomSize, wallThickness * 2});
	southPassage.setPosition(
		{room.getPosition().x, room.getPosition().y + roomSize});
	southPassage.setFillColor(sf::Color::Black);
}

void MazeCell::draw(QtSfmlCanvas* canvas)
{
	canvas->draw(room);
	canvas->draw(eastPassage);
	canvas->draw(southPassage);
}

void MazeCell::openSouthPassage()
{
	southPassage.setFillColor(sf::Color::Cyan);
}

void MazeCell::openEastPassage()
{
	eastPassage.setFillColor(sf::Color::Cyan);
}

MazePrinter::MazePrinter(QtSfmlCanvas* canvas)
	: canvas(canvas)
	, border({600 - wallThickness * 2, 480 - wallThickness * 2})
{
	border.setPosition({wallThickness, wallThickness});
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

void MazePrinter::updateMaze(const Maze& maze)
{
	for (const auto& passage : maze)
	{
		auto& [source, dest] = passage;

		if (source.row == dest.row)
		{
			auto column = std::min({source.column, source.row});
			mazeGrid[source.row][column].openEastPassage();
		}
		else
		{
			auto row = std::min({source.row, dest.row});
			mazeGrid[row][source.column].openSouthPassage();
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