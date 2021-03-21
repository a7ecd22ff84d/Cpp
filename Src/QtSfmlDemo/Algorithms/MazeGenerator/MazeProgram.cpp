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

void MazeProgram::run()
{
	displayTimer->start();
}

void MazeProgram::reset()
{
	generator.reset();
	printer.init();
	updateState(ProgramState::preparation);
}

void MazeProgram::update()
{
	printer.draw();
	printer.updateMaze(generator.getMaze());
}

void MazeProgram::nextStep()
{
	auto completed = !generator.step();
	printer.updateMaze(generator.getMaze());

	if (completed)
	{
		animationTimer.stop();
		ui->runPauseButton->setText("Run");
		updateState(ProgramState::completed);
	}
}

void MazeProgram::toogleAnimation()
{
	if (state != ProgramState::animation)
		updateState(ProgramState::animation);
	else
		updateState(ProgramState::generation);
}

void MazeProgram::connectTimers()
{
	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	connect(displayTimer, &QTimer::timeout, this, &MazeProgram::update);

	connect(&animationTimer, &QTimer::timeout, this, &MazeProgram::nextStep);
}

void MazeProgram::connectControls()
{
	connect(ui->nextStepButton, &QPushButton::clicked, this, &MazeProgram::nextStep);
	connect(ui->runPauseButton, &QPushButton::clicked, this, &MazeProgram::toogleAnimation);
	connect(ui->resetButton, &QPushButton::clicked, this, &MazeProgram::reset);
}

void MazeProgram::updateState(ProgramState newState)
{
	state = newState;

	bool readyToGenerate =
		state == ProgramState::preparation || state == ProgramState::generation;

	ui->nextStepButton->setEnabled(readyToGenerate);
	ui->animationSpeedSpinBox->setEnabled(readyToGenerate);
	ui->runPauseButton->setEnabled(state != ProgramState::completed);
	setAnimationEnabled(state == ProgramState::animation);
}

void MazeProgram::setAnimationEnabled(bool enabled)
{
	if (enabled && !animationTimer.isActive())
	{
		auto stepsPerSecond = ui->animationSpeedSpinBox->value();
		animationTimer.setInterval(std::chrono::milliseconds(1000 / stepsPerSecond));
		animationTimer.start();
		ui->runPauseButton->setText("Pause");
	}
	else if (!enabled && animationTimer.isActive())
	{
		animationTimer.stop();
		ui->runPauseButton->setText("Run");
	}
}