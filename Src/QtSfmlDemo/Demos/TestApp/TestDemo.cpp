#include "QtSfmlDemo/Demos/TestApp/TestDemo.h"

#include "QtSfmlDemo/Demos/TestApp/GameState.h"

void TestDemo::init(QtSfmlCanvas* canvas)
{
	initGameState();
	initTimer();
	gameEngine = std::make_unique<GameEngine>(canvas);
	gameEngine->setState(initialState);
}

void TestDemo::run()
{
	timer.start();
}

void TestDemo::initTimer()
{
	timer.setInterval(std::chrono::milliseconds(1000 / 60));
	timer.connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
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
	// // direction buttons
	// connect(ui->leftButton, &QPushButton::released, [this]() {
	// 	gameEngine->move(Direction::Left, ui->stepSpinBox->value());
	// });

	// connect(ui->rightButton, &QPushButton::released, [this]() {
	// 	gameEngine->move(Direction::Right, ui->stepSpinBox->value());
	// });

	// connect(ui->upButton, &QPushButton::released, [this]() {
	// 	gameEngine->move(Direction::Up, ui->stepSpinBox->value());
	// });

	// connect(ui->downButton, &QPushButton::released, [this]() {
	// 	gameEngine->move(Direction::Down, ui->stepSpinBox->value());
	// });

	// // reset button
	// connect(ui->resetButton, &QPushButton::released, [this]() {
	// 	gameEngine->setState(this->initialState);
	// });
}

void TestDemo::update()
{
	gameEngine->draw();

	// 	auto position = gameEngine->getState()->circle.getPosition();
	// 	ui->positionLabel->setText(
	// 		fmt::format("Position: x={0}, y={1}", position.x, position.y).c_str());
}
