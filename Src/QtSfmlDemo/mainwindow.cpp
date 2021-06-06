#include "QtSfmlDemo/mainwindow.h"

#include <memory>
#include <string_view>

#include <QAction>

#include "./ui_mainwindow.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"
#include "QtSfmlDemo/Demos/Init/InitProgram.h"
#include "QtSfmlDemo/Demos/TestApp/TestDemo.h"

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
	reset("Maze generator");
}

MainWindow::~MainWindow()
{
	delete ui;
}

template<typename T>
void MainWindow::registerDemo(QMenu* menu, std::string_view name)
{
	demoFactory.registerType(name, [&]() -> std::unique_ptr<Qsd::BaseDemo> {
		return std::make_unique<T>(context);
	});

	auto newAction = menu->addAction(QString(name.data()));
	connect(newAction, &QAction::triggered, [this, name]() { reset(name); });
}

void MainWindow::registerDemos()
{
	registerDemo<Qsd::MazeProgram>(ui->algorithmsMenu, "Maze generator");

	registerDemo<Qsd::InitialProgram>(ui->demosMenu, "Initial program");
	registerDemo<Qsd::TestDemo>(ui->demosMenu, "Controls test");
}

void MainWindow::reset(std::string_view name)
{
	timer.disconnect();
	currentProgram = demoFactory.create(name);
	currentProgram->run();
}