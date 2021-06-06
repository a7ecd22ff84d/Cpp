#include "QtSfmlDemo/Demos/TestApp/TestDemo.h"

#include "QtSfmlDemo/Demos/TestApp/GameControls.h"
#include "QtSfmlDemo/Demos/TestApp/GameState.h"

namespace Qsd
{
TestDemo::TestDemo(const DemoContext& context)
	: BaseDemo(context)
	, gameEngine(std::make_unique<GameEngine>(canvas))
	, controls(new GameControls(context.controlsWidget, gameEngine.get()))
{
}

TestDemo::~TestDemo()
{
	delete controls;
}

void TestDemo::run()
{
	initGameState();
	initTimer();
	gameEngine->setState(initialState);

	displayTimer->start();
	controls->show();
}

QString TestDemo::getDescription() const
{
	return "Simple test program, nothin interesting here.";
}

void TestDemo::initTimer()
{
	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	displayTimer->connect(displayTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void TestDemo::initGameState()
{
	initialState.circle = sf::CircleShape(20);
	initialState.circle.setFillColor(sf::Color::Green);
	initialState.circle.setPosition(100, 100);

	const int thickness = 5;
	initialState.boundaries =
		sf::RectangleShape({600 - 2 * thickness, 480 - 2 * thickness});

	initialState.boundaries.setOutlineColor(sf::Color::Red);
	initialState.boundaries.setFillColor(sf::Color::Transparent);
	initialState.boundaries.setOutlineThickness(thickness);
	initialState.boundaries.setPosition({thickness, thickness});
}

void TestDemo::connectButtonsToEngine()
{
}

void TestDemo::update()
{
	gameEngine->draw();

	// auto position = gameEngine->getState()->circle.getPosition();
	// ui->positionLabel->setText(
	// 	fmt::format("Position: x={0}, y={1}", position.x, position.y).c_str());
}

} // namespace Qsd