#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include <QPushButton>
#include <QSpinBox>

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

	reset();
}

void MazeProgram::run()
{
	displayTimer->start();
}

void MazeProgram::reset()
{
	printer.init(ui->width->value(), ui->height->value());
	generator.initNewMaze(ui->width->value(), ui->height->value());
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
		updateState(ProgramState::completed);
	else if (state != ProgramState::animation)
		updateState(ProgramState::generation);
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
	connect(
		ui->width,
		(void (QSpinBox::*)(int)) & QSpinBox::valueChanged,
		[this](int i) { reset(); });

	connect(
		ui->height,
		(void (QSpinBox::*)(int)) & QSpinBox::valueChanged,
		[&](int height) { reset(); });
}

void MazeProgram::updateState(ProgramState newState)
{
	if (state == newState)
		return;

	bool readyToGenerate = newState == ProgramState::preparation
		|| newState == ProgramState::generation;

	ui->nextStepButton->setEnabled(readyToGenerate);
	ui->animationSpeedSpinBox->setEnabled(readyToGenerate);
	ui->runPauseButton->setEnabled(newState != ProgramState::completed);
	ui->width->setEnabled(newState == ProgramState::preparation);
	ui->height->setEnabled(newState == ProgramState::preparation);
	setAnimationEnabled(newState == ProgramState::animation);

	if (newState == ProgramState::preparation)
		printer.init(ui->width->value(), ui->height->value());

	if (state == ProgramState::preparation)
	{
		printer.init(ui->width->value(), ui->height->value());
		generator.initNewMaze(ui->width->value(), ui->height->value());
	}

	state = newState;
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