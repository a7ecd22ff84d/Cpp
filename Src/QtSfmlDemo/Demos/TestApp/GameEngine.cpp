#include "QtSfmlDemo/Demos/TestApp/GameEngine.h"

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Demos/TestApp/GameState.h"

GameEngine::GameEngine(QtSfmlCanvas* qtSfmlCanvas) : canvas(qtSfmlCanvas)
{
}

void GameEngine::setState(GameState gameState)
{
	state = gameState;
}

void GameEngine::move(Direction direction, int distance)
{
	if (direction == Direction::Left)
		state.circle.move(-distance, 0);
	else if (direction == Direction::Right)
		state.circle.move(distance, 0);
	if (direction == Direction::Up)
		state.circle.move(0, -distance);
	else if (direction == Direction::Down)
		state.circle.move(0, distance);
}

const GameState* GameEngine::getState() const
{
	return &state;
}

void GameEngine::draw()
{
	canvas->clear();
	canvas->draw(state.circle);
	canvas->draw(state.boundaries);
	canvas->display();
}
