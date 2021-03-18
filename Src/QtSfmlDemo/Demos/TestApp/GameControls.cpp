#include "GameControls.h"

#include "QtSfmlDemo/Demos/TestApp/GameEngine.h"
#include "ui_GameControls.h"

GameControls::GameControls(QWidget* parent, GameEngine* gameEngine)
	: QWidget(parent)
	, ui(new Ui::GameControls)
    , gameEngine(gameEngine)
{
	ui->setupUi(this);
	connectControlsToEngine();
}

GameControls::~GameControls()
{
	delete ui;
}

void GameControls::connectControlsToEngine()
{
	// direction buttons
	connect(ui->leftButton, &QPushButton::released, [this]() {
		gameEngine->move(Direction::Left, ui->stepSpinBox->value());
	});

	connect(ui->rightButton, &QPushButton::released, [this]() {
		gameEngine->move(Direction::Right, ui->stepSpinBox->value());
	});

	connect(ui->upButton, &QPushButton::released, [this]() {
		gameEngine->move(Direction::Up, ui->stepSpinBox->value());
	});

	connect(ui->downButton, &QPushButton::released, [this]() {
		gameEngine->move(Direction::Down, ui->stepSpinBox->value());
	});

	// // reset button
	// connect(ui->resetButton, &QPushButton::released, [this]() {
	// 	gameEngine->setState(this->initialState);
	// });
}