#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

#include <SFML/Graphics/Color.hpp>

MazePrinter::MazePrinter(QtSfmlCanvas* canvas) : canvas(canvas), shape(20)
{
	shape.setFillColor(sf::Color::Cyan);
	shape.setPosition({100, 100});
}

void MazePrinter:: draw()
{
	canvas->clear();
	canvas->draw(shape);
	canvas->display();	
}