#ifndef __GAME_ENGINE_H
#define __GAME_ENGINE_H

#include <SFML/Graphics/CircleShape.hpp>

#include "QtSfml/GameState.h"
#include "QtSfml/QtSfmlCanvas.h"

enum class Direction
{
	Left,
	Right,
	Up,
	Down,
};

class GameEngine
{
public:
	GameEngine(QtSfmlCanvas* qtSfmlCanvas);

	void setState(GameState gameState);
	void move(Direction direction, int distance);
	void draw();

	const GameState* getState() const;

private:
	QtSfmlCanvas* canvas;
	GameState state;
};

#endif // __GAME_ENGINE_H