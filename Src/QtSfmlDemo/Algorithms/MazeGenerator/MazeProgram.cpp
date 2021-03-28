#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include <memory>

#include <QPushButton>
#include <QSpinBox>

#include "Core/Generator/Maze/IMazeGenerator.h"
#include "Core/Generator/Maze/RecursiveBacktrackingGenerator.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"
#include "ui_MazeControls.h"

MazeProgram::MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer)
	: canvas(canvas)
	, ui(new Ui::MazeControls)
	, displayTimer(timer)
	, printer(MazePrinter(canvas))
	, generator(std::make_unique<RecursiveBacktrackingGenerator>())
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
	generator->initNewMaze(getContext());
	updateState(ProgramState::preparation);
}

void MazeProgram::update()
{
	printer.draw();
}

void MazeProgram::nextStep()
{
	auto completed = !generator->step();
	printer.updateMaze(generator->getMaze());

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

void MazeProgram::generateAll()
{
	updateState(ProgramState::generation);

	while (generator->step())
		; // :)

	printer.updateMaze(generator->getMaze());
	updateState(ProgramState::completed);
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
	connect(ui->generateMazeButton, &QPushButton::clicked, this, &MazeProgram::generateAll);

	// TODO: C++20 template lambda instead of maually creating one for each ui
	// control auto callReset = [&]<T>(const T& text) { reset(); };

	// there are two methods with the same name, I have to specify
	// which method I'm using by writing '(void (QSpinBox::*)(int))'
	connect(ui->width, (void (QSpinBox::*)(int)) & QSpinBox::valueChanged, [&](int i) {
		reset();
	});
	connect(
		ui->height,
		(void (QSpinBox::*)(int)) & QSpinBox::valueChanged,
		[&](int height) { reset(); });

	connect(ui->seedEdit, &QLineEdit::textChanged, [&](const QString& text) {
		reset();
	});
}

void MazeProgram::updateState(ProgramState newState)
{
	if (state == newState)
		return;

	bool readyToGenerate = newState == ProgramState::preparation
		|| newState == ProgramState::generation;

	ui->nextStepButton->setEnabled(readyToGenerate);
	ui->animationSpeedSpinBox->setEnabled(readyToGenerate);
	ui->generateMazeButton->setEnabled(readyToGenerate);
	ui->runPauseButton->setEnabled(newState != ProgramState::completed);
	ui->width->setEnabled(newState == ProgramState::preparation);
	ui->height->setEnabled(newState == ProgramState::preparation);
	ui->seedEdit->setEnabled(newState == ProgramState::preparation);
	setAnimationEnabled(newState == ProgramState::animation);

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

GeneratorContext MazeProgram::getContext()
{
	auto context = GeneratorContext();
	context.width = ui->width->value();
	context.height = ui->height->value();
	context.seed = ui->seedEdit->text().toStdString();

	return context;
}
