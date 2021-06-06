#ifndef __TEST_DEMO_H
#define __TEST_DEMO_H

#include <QWidget>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/BaseDemo.h"
#include "QtSfmlDemo/Demos/TestApp/GameControls.h"
#include "QtSfmlDemo/Demos/TestApp/GameEngine.h"
#include "QtSfmlDemo/Demos/TestApp/GameState.h"

namespace Qsd
{
class TestDemo : public BaseDemo
{
	Q_OBJECT

public:
	TestDemo(const DemoContext& context);

	~TestDemo();

	virtual void run() final;

private:
	void initTimer();
	void initGameState();

	void connectButtonsToEngine();

private slots:
	void update();

private:
	std::unique_ptr<GameEngine> gameEngine;
	GameControls* controls;
	GameState initialState;
};

} // namespace Qsd

#endif