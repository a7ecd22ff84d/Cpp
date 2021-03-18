#ifndef __TEST_DEMO_H
#define __TEST_DEMO_H

#include <QWidget>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Demos/TestApp/GameControls.h"
#include "QtSfmlDemo/Demos/TestApp/GameEngine.h"
#include "QtSfmlDemo/Demos/TestApp/GameState.h"

class TestDemo : public QObject
{
	Q_OBJECT

public:
	void init(QtSfmlCanvas* canvas, QWidget* controlsWidget);
	void run();

private:
	void initTimer();
	void initGameState();

	void connectButtonsToEngine();

private slots:
	void update();

private:
	GameControls* controls;
	QTimer timer;
	GameState initialState;
	std::unique_ptr<GameEngine> gameEngine;
};

#endif