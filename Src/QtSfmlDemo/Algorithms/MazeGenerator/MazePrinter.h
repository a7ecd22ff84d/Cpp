#ifndef __MAZE_PRINTER_H
#define __MAZE_PRINTER_H

#include <array>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

class MazeCell
{
public:
	MazeCell(){};
	MazeCell(int row, int column);
	void draw(QtSfmlCanvas* canvas);
	void openSouthPassage(bool inStack);
	void openEastPassage(bool inStack);
	void paintRoom(sf::Color color);

private:
	sf::RectangleShape room;
	sf::RectangleShape eastPassage;
	sf::RectangleShape southPassage;
};

class MazePrinter
{
	using MazeGrid = std::array<std::array<MazeCell, 30>, 24>;

public:
	MazePrinter(QtSfmlCanvas* canvas);

	void updateMaze(const Maze& maze);
	void draw();

private:
	void init();
	void printRooms(const Maze& maze);
	void printPassages(const Maze& maze);
	bool isPassageInStack(const Maze& maze, const Passage& passage) const;

private:
	QtSfmlCanvas* canvas;
	sf::RectangleShape border;
	MazeGrid mazeGrid;
};

#endif // __MAZE_PRINTER_H