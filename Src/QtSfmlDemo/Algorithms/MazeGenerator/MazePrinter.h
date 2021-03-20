#ifndef __MAZE_PRINTER_H
#define __MAZE_PRINTER_H

#include <array>

#include <SFML/Graphics/RectangleShape.hpp>

#include "QtSfml/QtSfmlCanvas.h"

class MazeCell
{
public:
	MazeCell(){};
	MazeCell(int x, int y);
	void draw(QtSfmlCanvas* canvas);

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

	void init();
	void draw();

private:
	QtSfmlCanvas* canvas;
	sf::RectangleShape border;
	MazeGrid mazeGrid;
};

#endif // __MAZE_PRINTER_H