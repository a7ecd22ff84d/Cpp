#include "QtSfml/GameEngine.h"

#include "QtSfml/QtSfmlCanvas.h"

GameEngine::GameEngine(QtSfmlCanvas* qtSfmlCanvas, std::chrono::milliseconds frameTime)
	: canvas(qtSfmlCanvas)
	, frameTime(frameTime)
	, shape(20)
{
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);

	timer.setInterval(frameTime);
	timer.connect(&timer, SIGNAL(timeout()), this, SLOT(draw()));
}

void GameEngine::init()
{
	timer.start();
}

void GameEngine::move(Direction direction, int distance)
{
	if (direction == Direction::Left)
		shape.move(-distance, 0);
	else if (direction == Direction::Right)
		shape.move(distance, 0);
	if (direction == Direction::Up)
		shape.move(0, -distance);
	else if (direction == Direction::Down)
		shape.move(0, distance);
}

void GameEngine::reset()
{
	// Todo: tu aż się prosi o użycie wzorca stan :)
	shape.setPosition(100, 100);
}

void GameEngine::draw()
{
	canvas->clear();
	canvas->draw(shape);
	canvas->display();
}
