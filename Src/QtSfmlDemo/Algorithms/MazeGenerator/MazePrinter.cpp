#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Core/SfmlTools/Color.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

const int wallThickness = 2;
const int cellSize = 20;
const int roomSize = cellSize - 2 * wallThickness;

MazeCell::MazeCell(int row, int column)
{
	sf::Vector2f cellPosition(column * cellSize, row * cellSize);

	room = sf::RectangleShape({roomSize, roomSize});
	room.setPosition(
		column * cellSize + wallThickness, row * cellSize + wallThickness);
	room.setFillColor(SfmlTools::Color::grey);

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
		southPassage.setFillColor(SfmlTools::Color::darkRed);
	else
		southPassage.setFillColor(sf::Color::Red);
}

void MazeCell::openEastPassage(bool inStack)
{
	if (inStack)
		eastPassage.setFillColor(SfmlTools::Color::darkRed);
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
}

void MazePrinter::updateMaze(const Maze& maze)
{
	printRooms(maze);
	printPassages(maze);
}

void MazePrinter::draw()
{
	canvas->clear();
	for (unsigned row = 0; row < mazeGrid.size(); row++)
	{
		for (unsigned column = 0; column < mazeGrid[row].size(); column++)
		{
			mazeGrid[row][column].draw(canvas);
		}
	}
	canvas->draw(border);
	canvas->display();
}

void MazePrinter::init(unsigned width, unsigned height)
{
	mazeGrid = std::vector<std::vector<MazeCell>>(height);

	for (unsigned row = 0; row < height; row++)
	{
		mazeGrid[row] = std::vector<MazeCell>(width);

		for (unsigned column = 0; column < width; column++)
		{
			mazeGrid[row][column] = MazeCell(row, column);
		}
	}

	canvas->setViewArea(
		sf::Vector2f(width * cellSize / 2.0, height * cellSize / 2.0),
		sf::Vector2f(width * cellSize, height * cellSize));
}

void MazePrinter::printRooms(const Maze& maze)
{
	for (int row = 0; row < maze.height; row++)
	{
		for (int column = 0; column < maze.width; column++)
		{
			auto status = maze.cellStatuses[row][column];

			switch (status)
			{
			case CellStatus::notVisited:
				mazeGrid[row][column].paintRoom(SfmlTools::Color::grey);
				break;
			case CellStatus::visited:
				mazeGrid[row][column].paintRoom(sf::Color::Red);
				break;
			case CellStatus::active:
				mazeGrid[row][column].paintRoom(sf::Color::Blue);
				break;
			case CellStatus::inStack:
				mazeGrid[row][column].paintRoom(SfmlTools::Color::darkRed);
				break;
			}
		}
	}
}

void MazePrinter::printPassages(const Maze& maze)
{
	for (const auto& passage : maze.passages)
	{
		auto& [source, dest] = passage;
		bool inStack = isPassageInStack(maze, passage);

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
}

bool MazePrinter::isPassageInStack(const Maze& maze, const Passage& passage) const
{
	auto& [src, dest] = passage;

	auto srcStatus = maze.cellStatuses[src.row][src.column];
	auto destStatus = maze.cellStatuses[dest.row][dest.column];

	return (destStatus == CellStatus::inStack || destStatus == CellStatus::active)
		&& (srcStatus == CellStatus::inStack || srcStatus == CellStatus::active);
}
