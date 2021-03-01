#include "QtSfml/GameEngine.h"

#include "QtSfml/QtSfmlCanvas.h"

GameEngine::GameEngine(QtSfmlCanvas* qtSfmlCanvas, std::chrono::milliseconds frameTime)
	: canvas(qtSfmlCanvas)
	, frameTime(frameTime)
	, shape(20)
{
	shape.setFillColor(sf::Color::Green);

	timer.setInterval(frameTime);
	timer.connect(&timer, SIGNAL(timeout()), this, SLOT(draw()));
}

void GameEngine::init()
{
	timer.start();
}

void GameEngine::draw()
{
	canvas->draw(shape);
	canvas->display();
}
