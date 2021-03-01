#ifndef __GAME_ENGINE_H
#define __GAME_ENGINE_H

#include <chrono>

#include <QObject>
#include <QTimer>
#include <SFML/Graphics/CircleShape.hpp>

#include "QtSfml/QtSfmlCanvas.h"

enum class Direction
{
	Left,
	Right,
	Up,
	Down,
};

class GameEngine : public QObject
{
	Q_OBJECT

public:
	GameEngine(QtSfmlCanvas* qtSfmlCanvas, std::chrono::milliseconds frameTime);
	void init();

	void move(Direction direction, int distance);
	void reset();

private slots:
	void draw();

private:
	QtSfmlCanvas* canvas;
	std::chrono::milliseconds frameTime;
	QTimer timer;

	// objects on screen
	sf::CircleShape shape;
};

#endif // __GAME_ENGINE_H