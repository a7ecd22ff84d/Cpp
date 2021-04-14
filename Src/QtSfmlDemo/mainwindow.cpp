#include "QtSfmlDemo/mainwindow.h"

#include <memory>

#include <QAction>

#include "./ui_mainwindow.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	initMenuButtons();

	ui->actionMazeGenerator->triggered();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initMenuButtons()
{
	connect(ui->actionInit, &QAction::triggered, [this]() {
		reset();
		initialProgram = std::make_unique<InitialProgram>();
		initialProgram->init(ui->sfmlWindow);
		initialProgram->run();
	});

	connect(ui->actionControlsTest, &QAction::triggered, [this]() {
		reset();
		testDemo = std::make_unique<TestDemo>();
		testDemo->init(ui->sfmlWindow, ui->controlsWidget);
		testDemo->run();
	});

	connect(ui->actionMazeGenerator, &QAction::triggered, [this]() {
		reset();
		mazeProgram = std::make_unique<MazeProgram>(
			ui->sfmlWindow, ui->controlsWidget, ui->statusbar, &timer);
		mazeProgram->run();
	});
}

void MainWindow::reset()
{
	timer.disconnect();
	initialProgram.reset();
	testDemo.reset();
	mazeProgram.reset();
}