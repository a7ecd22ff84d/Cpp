#include "QtSfml/mainwindow.h"

#include <chrono>
#include <memory>

#include "./ui_mainwindow.h"
#include "QtSfml/GameEngine.h"
#include "QtSfml/QtSfmlCanvas.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	gameEngine = std::make_unique<GameEngine>(
		ui->sfmlWindow, std::chrono::milliseconds(1000 / 60));

	connectButtonsToEngine();
	gameEngine->init();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::connectButtonsToEngine()
{
	// direction buttons
	connect(ui->leftButton, &QPushButton::released, [=]() {
		gameEngine->move(Direction::Left, ui->stepSpinBox->value());
	});

	connect(ui->rightButton, &QPushButton::released, [=]() {
		gameEngine->move(Direction::Right, ui->stepSpinBox->value());
	});

	connect(ui->upButton, &QPushButton::released, [=]() {
		gameEngine->move(Direction::Up, ui->stepSpinBox->value());
	});

	connect(ui->downButton, &QPushButton::released, [=]() {
		gameEngine->move(Direction::Down, ui->stepSpinBox->value());
	});

	// reset button
	connect(ui->resetButton, &QPushButton::released, [=]() {
		gameEngine->reset();
	});
}
