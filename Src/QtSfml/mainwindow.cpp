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
	gameEngine->init();
}

MainWindow::~MainWindow()
{
	delete ui;
}
