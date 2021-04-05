#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include <memory>
#include <string_view>

#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>

#include "Core/Generator/Maze/IMazeGenerator.h"
#include "Core/Generator/Maze/Maze.h"
#include "Core/Generator/Maze/RecursiveBacktrackingGenerator.h"
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
	registerGenerators();

	reset();
}

void MazeProgram::run()
{
	displayTimer->start();
}

void MazeProgram::reset()
{
	generator->initNewMaze(getContext());
	printer.init(ui->width->value(), ui->height->value());
	updateState(ProgramState::preparation);
}

void MazeProgram::update()
{
	printer.draw();
}

void MazeProgram::algorithmChanged(int index)
{
	auto itemText = ui->algorithmCombo->itemText(index);

	std::cout << "switching to: " << itemText.toStdString() <<"\n";

	generator = generatorFactory.create(itemText.toStdString());
	reset();
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
	connect(
		ui->algorithmCombo,
		QOverload<int>::of(&QComboBox::currentIndexChanged),
		this,
		&MazeProgram::algorithmChanged);

	// TODO: C++20 template lambda instead of maually creating one for each ui
	// control auto callReset = [&]<T>(const T& text) { reset(); };
	connect(ui->width, QOverload<int>::of(&QSpinBox::valueChanged), [&](int i) {
		reset();
	});

	connect(ui->height, QOverload<int>::of(&QSpinBox::valueChanged), [&](int height) {
		reset();
	});

	connect(ui->seedEdit, &QLineEdit::textChanged, [&](const QString& text) {
		reset();
	});
}

void MazeProgram::registerGenerators()
{
	generatorFactory.registerGenerator(
		"Randomized depth-first search", []() -> std::unique_ptr<IMazeGenerator> {
			return std::make_unique<RecursiveBacktrackingGenerator>();
		});

	generatorFactory.registerGenerator(
		"Randomized Kruskal's", []() -> std::unique_ptr<IMazeGenerator> {
			return std::make_unique<RecursiveBacktrackingGenerator>(); // TODO: tymczasow
		});

	for (const auto& item: generatorFactory.getRegisteredObjectNames())
		ui->algorithmCombo->addItem(item.data());
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
