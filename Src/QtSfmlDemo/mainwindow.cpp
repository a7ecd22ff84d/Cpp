#include "QtSfmlDemo/mainwindow.h"

#include <memory>
#include <string_view>

#include <QAction>

#include "./ui_mainwindow.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"
#include "QtSfmlDemo/BaseDemo.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	context.controlsWidget = ui->controlsWidget;
	context.canvas = ui->sfmlWindow;
	context.statusBar = ui->statusbar;
	context.timer = &timer;

	registerDemos();
	initMenuButtons();
	ui->actionMazeGenerator->triggered();

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::registerDemos()
{
	demoFactory.registerType("initProgram", [&]() -> std::unique_ptr<Qsd::BaseDemo> {
		return std::make_unique<Qsd::InitialProgram>(context);
	});

	demoFactory.registerType("controlsTest", [&]() -> std::unique_ptr<Qsd::BaseDemo> {
		return std::make_unique<Qsd::TestDemo>(context);
	});

	demoFactory.registerType(
		"mazeGenerator", [&]() -> std::unique_ptr<Qsd::BaseDemo> {
			return std::make_unique<Qsd::MazeProgram>(context);
		});
}

void MainWindow::initMenuButtons()
{
	connect(ui->actionInit, &QAction::triggered, [this]() {
		reset("initProgram");
	});

	connect(ui->actionControlsTest, &QAction::triggered, [this]() {
		reset("controlsTest");
	});

	connect(ui->actionMazeGenerator, &QAction::triggered, [this]() {
		reset("mazeGenerator");
	});
}

void MainWindow::reset(std::string_view name)
{
	timer.disconnect();
	currentProgram = demoFactory.create(name);
	currentProgram->run();
}