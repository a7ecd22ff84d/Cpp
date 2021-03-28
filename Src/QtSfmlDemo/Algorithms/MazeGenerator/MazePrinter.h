#ifndef __MAZE_PRINTER_H
#define __MAZE_PRINTER_H

#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Core/Generator/Maze/Maze.h"
#include "QtSfml/QtSfmlCanvas.h"

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
	using MazeGrid = std::vector<std::vector<MazeCell>>;

public:
	MazePrinter(QtSfmlCanvas* canvas);

	void updateMaze(const Maze& maze);
	void draw();
	void init(unsigned width, unsigned height);

private:
	void printRooms(const Maze& maze);
	void printPassages(const Maze& maze);
	bool isPassageInStack(const Maze& maze, const Passage& passage) const;

private:
	QtSfmlCanvas* canvas;
	sf::RectangleShape border;
	MazeGrid mazeGrid;
};

#endif // __MAZE_PRINTER_H