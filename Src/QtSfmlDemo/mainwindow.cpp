#include "QtSfmlDemo/mainwindow.h"

#include <memory>

#include <QAction>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	initMenuButtons();

	ui->actionControlsTest->triggered();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initMenuButtons()
{
	connect(ui->actionInit, &QAction::triggered, [this]() {
		testDemo.reset();
		initialProgram = std::make_unique<InitialProgram>();
		initialProgram->init(ui->sfmlWindow);
		initialProgram->run();
	});

	connect(ui->actionControlsTest, &QAction::triggered, [this]() {
		initialProgram.reset();
		testDemo = std::make_unique<TestDemo>();
		testDemo->init(ui->sfmlWindow);
		testDemo->run();
	});
}
