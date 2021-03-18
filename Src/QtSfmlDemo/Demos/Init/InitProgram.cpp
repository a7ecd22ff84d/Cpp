#include "QtSfmlDemo/Demos/Init/InitProgram.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

InitialProgram::InitialProgram() : shape(20)
{
}

void InitialProgram::init(QtSfmlCanvas* canvas)
{
	this->canvas = canvas;

	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);
}

void InitialProgram::run()
{
	canvas->clear();
	canvas->draw(shape);
	canvas->display();

	initTimer();
	timer.start();
}

void InitialProgram::initTimer()
{
	timer.setInterval(std::chrono::milliseconds(1000 / 60));
	timer.connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

void InitialProgram::update()
{
	canvas->clear();
	canvas->draw(shape);
	canvas->display();
}