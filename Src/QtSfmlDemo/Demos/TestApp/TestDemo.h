#ifndef __TEST_DEMO_H
#define __TEST_DEMO_H

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Demos/TestApp/GameEngine.h"
#include "QtSfmlDemo/Demos/TestApp/GameState.h"

class TestDemo : public QObject
{
	Q_OBJECT

public:

	void init(QtSfmlCanvas* canvas);
	void run();

private:
	void initTimer();
	void initGameState();

	void connectButtonsToEngine();

private slots:
	void update();

private:
	QTimer timer;
	GameState initialState;
	std::unique_ptr<GameEngine> gameEngine;
};

#endif