#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include <QPushButton>

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"
#include "ui_MazeControls.h"

MazeProgram::MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer)
	: canvas(canvas)
	, ui(new Ui::MazeControls)
	, displayTimer(timer)
	, printer(MazePrinter(canvas))
{
	ui->setupUi(controlsWidget);
	connectTimers();
	connectControls();
}

void MazeProgram::connectTimers()
{
	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	connect(displayTimer, &QTimer::timeout, this, &MazeProgram::update);

	animationTimer.setInterval(std::chrono::milliseconds(10));
	connect(&animationTimer, &QTimer::timeout, this, &MazeProgram::nextStep);
}

void MazeProgram::connectControls()
{
	connect(ui->nextStepButton, &QPushButton::clicked, this, &MazeProgram::nextStep);
	connect(ui->runPauseButton, &QPushButton::clicked, this, &MazeProgram::toogleAnimation);
}

void MazeProgram::run()
{
	displayTimer->start();
}

void MazeProgram::update()
{
	printer.draw();
}

void MazeProgram::nextStep()
{
	auto completed = !generator.step();
	printer.updateMaze(generator.getMaze());

	if (completed)
		animationTimer.stop();
}

void MazeProgram::toogleAnimation()
{
	if (animationTimer.isActive())
	{
		animationTimer.stop();
		ui->runPauseButton->setText("Run");
	}
	else
	{
		animationTimer.start();
		ui->runPauseButton->setText("Pause");
	}
}