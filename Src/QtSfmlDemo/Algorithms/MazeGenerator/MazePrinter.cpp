#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

const int wallThickness = 2;
const int cellSize = 20;
const int roomSize = cellSize - 2 * wallThickness;

sf::Color grey{50, 50, 50};
sf::Color darkRed{100, 20, 20};

MazeCell::MazeCell(int row, int column)
{
	sf::Vector2f cellPosition(column * cellSize, row * cellSize);

	room = sf::RectangleShape({roomSize, roomSize});
	room.setPosition(
		column * cellSize + wallThickness, row * cellSize + wallThickness);
	room.setFillColor(grey);

	sf::Vector2f roomPosition = room.getPosition();
	eastPassage = sf::RectangleShape({wallThickness * 2, roomSize});
	eastPassage.setPosition({roomPosition.x + roomSize, roomPosition.y});
	eastPassage.setFillColor(sf::Color::Black);

	southPassage = sf::RectangleShape({roomSize, wallThickness * 2});
	southPassage.setPosition({roomPosition.x, roomPosition.y + roomSize});
	southPassage.setFillColor(sf::Color::Black);
}

void MazeCell::draw(QtSfmlCanvas* canvas)
{
	canvas->draw(room);
	canvas->draw(eastPassage);
	canvas->draw(southPassage);
}

void MazeCell::openSouthPassage(bool inStack)
{
	if (inStack)
		southPassage.setFillColor(darkRed);
	else
		southPassage.setFillColor(sf::Color::Red);
}

void MazeCell::openEastPassage(bool inStack)
{
	if (inStack)
		eastPassage.setFillColor(darkRed);
	else
		eastPassage.setFillColor(sf::Color::Red);
}

void MazeCell::paintRoom(sf::Color color)
{
	room.setFillColor(color);
}

MazePrinter::MazePrinter(QtSfmlCanvas* canvas)
	: canvas(canvas)
	, border({600 - wallThickness * 2, 480 - wallThickness * 2})
{
	border.setPosition({wallThickness, wallThickness});
	border.setOutlineThickness(wallThickness);
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::Transparent);

	init();
}

void MazePrinter::updateMaze(const Maze& maze)
{
	for (const auto& passage : maze.passages)
	{
		auto& [source, dest] = passage;

		bool inStack =
			(maze.cellStatuses[source.row][source.column] == CellStatus::inStack
			 || maze.cellStatuses[source.row][source.column] == CellStatus::active)
			&& (maze.cellStatuses[dest.row][dest.column] == CellStatus::inStack
				|| maze.cellStatuses[dest.row][dest.column] == CellStatus::active);

		if (source.row == dest.row)
		{
			auto column = std::min({source.column, dest.column});
			mazeGrid[source.row][column].openEastPassage(inStack);
		}
		else
		{
			auto row = std::min({source.row, dest.row});
			mazeGrid[row][source.column].openSouthPassage(inStack);
		}
	}

	for (int row = 0; row < 24; row++)
	{
		for (int column = 0; column < 30; column++)
		{
			auto status = maze.cellStatuses[row][column];

			switch (status)
			{
			case CellStatus::notVisited:
				mazeGrid[row][column].paintRoom(grey);
				break;
			case CellStatus::visited:
				mazeGrid[row][column].paintRoom(sf::Color::Red);
				break;
			case CellStatus::active:
				mazeGrid[row][column].paintRoom(sf::Color::Blue);
				break;
			case CellStatus::inStack:
				mazeGrid[row][column].paintRoom(darkRed);
				break;
			}
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
