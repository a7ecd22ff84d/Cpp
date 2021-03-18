#ifndef __MAZE_PRINTER_H
#define __MAZE_PRINTER_H

#include <SFML/Graphics/CircleShape.hpp>
#include <qobjectdefs.h>

#include "QtSfml/QtSfmlCanvas.h"

class MazePrinter
{
public:
	MazePrinter(QtSfmlCanvas* canvas);

	void draw();

private:
	QtSfmlCanvas* canvas;
	sf::CircleShape shape;
};

#endif // __MAZE_PRINTER_H