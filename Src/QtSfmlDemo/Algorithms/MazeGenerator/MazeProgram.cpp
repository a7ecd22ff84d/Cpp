#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include <filesystem>
#include <string_view>

#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>
#include <fmt/core.h>

#include "Core/Containers/Contains.h"
#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Mazes/Maze.h"
#include "Core/Mazes/RandomizedKruskals.h"
#include "Core/Mazes/RecursiveBacktrackingGenerator.h"
#include "Core/Random/RandomTextGenerator.h"
#include "Core/SfmlTools/ScreenCapturer.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"
#include "ui_MazeControls.h"

namespace Qsd
{
MazeProgram::MazeProgram(const DemoContext& context)
	: BaseDemo(context)
	, ui(new Ui::MazeControls)
	, printer(MazePrinter(canvas))
{
	ui->setupUi(this);
	ui->randomSeedButton->setIcon(QIcon(":/Icons/dice.svg"));

	connectTimers();
	connectControls();
	registerGenerators();

	// Required for triggering update of Qt controls state at beginning of program
	updateState(ProgramState::completed);
	updateState(ProgramState::preparation);
}

MazeProgram::~MazeProgram()
{
	delete ui;
}

void MazeProgram::run()
{
	displayTimer->start();
}

QString MazeProgram::getDescription() const
{
	return R"(
<h2>Maze generator</h2>
<p>My implementation of maze generation algorithms found in <a href="https://en.wikipedia.org/wiki/Maze_generation_algorithm">https://en.wikipedia.org/wiki/Maze_generation_algorithm</a></p>
<p>Whole project was inspired by this  <a href="https://www.youtube.com/watch?v=Y37-gB83HKE">video</a></p>
<h3>Currently available algorithms:<span id="Randomized_depth-first_search" class="mw-headline"></span></h3>
<ul>
<li>Randomized depth-first search - recursive implementation - </li>
<li>Randomized Kruskal's algorithm</li>
</ul>
	)";
}

void MazeProgram::reset()
{
	steps = 0;
	generator->initNewMaze(getContext());
	printer.init(ui->width->value(), ui->height->value());
	updateState(ProgramState::preparation);
}

void MazeProgram::update()
{
	fpsCounter.tick();
	printer.draw();
	statusBar->showMessage(
		fmt::format("Fps: {0:.2f}, Steps: {1}", fpsCounter.getFps(), steps).c_str());
}

void MazeProgram::algorithmChanged(int index)
{
	auto itemText = ui->algorithmCombo->itemText(index);
	generator = generatorFactory.create(itemText.toStdString());
	reset();
}

void MazeProgram::nextStep()
{
	auto completed = !generator->step();
	printer.updateMaze(generator->getMaze());

	if (completed)
	{
		updateState(ProgramState::completed);
	}
	else
	{
		steps++;

		if (state != ProgramState::animation)
			updateState(ProgramState::generation);
	}
}

void MazeProgram::toggleAnimation()
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
		steps++;

	printer.updateMaze(generator->getMaze());
	updateState(ProgramState::completed);
}

void MazeProgram::generateSeed()
{
	size_t randomSeedLength = 10;
	ui->seedEdit->setText(Random::generateRandomText(randomSeedLength).c_str());
}

void MazeProgram::saveImage()
{
	auto filter = "All files (*.*);;PNG(*.png);;JPG(*.jpg)";
	auto selectedFilter = QString("PNG(*.png)");

	auto filename = QFileDialog::getSaveFileName(
		this, "Save image as", "", filter, &selectedFilter);

	if (filename.isEmpty())
		return;

	using std::filesystem::path;
	auto extension = path(filename.toStdString()).extension().string();
	std::vector<std::string> availableExtensions{".bmp", ".jpg", ".png", ".tga"};

	if (!Containers::contains(availableExtensions, extension))
	{
		QMessageBox::warning(
			this,
			"Warning",
			"Incorrect image format.\nAvailable formats: bmp, jpg, png, tga.");

		return;
	}

	SfmlTools::ScreenCapturer(*canvas).saveScreenshot(filename.toStdString());
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
	connect(ui->runPauseButton, &QPushButton::clicked, this, &MazeProgram::toggleAnimation);
	connect(ui->resetButton, &QPushButton::clicked, this, &MazeProgram::reset);
	connect(ui->generateMazeButton, &QPushButton::clicked, this, &MazeProgram::generateAll);
	connect(ui->randomSeedButton, &QPushButton::clicked, this, &MazeProgram::generateSeed);
	connect(
		ui->algorithmCombo,
		QOverload<int>::of(&QComboBox::currentIndexChanged),
		this,
		&MazeProgram::algorithmChanged);

	// TODO: C++20 template lambda instead of manually creating one for each ui
	// control auto callReset = [&]<T>(const T& text) { reset(); };
	connect(
		ui->width,
		QOverload<int>::of(&QSpinBox::valueChanged),
		[&](int i) { reset(); });

	connect(
		ui->height,
		QOverload<int>::of(&QSpinBox::valueChanged),
		[&](int height) { reset(); });

	connect(
		ui->seedEdit,
		&QLineEdit::textChanged,
		[&](const QString& text) { reset(); });

	connect(ui->imageSaveButton, &QPushButton::clicked, this, &MazeProgram::saveImage);
}

void MazeProgram::registerGenerators()
{
	generatorFactory.registerType<Mazes::RecursiveBacktrackingGenerator>(
		"Randomized depth-first search");

	generatorFactory.registerType<Mazes::RandomizedKruskals>("Randomized Kruskal's");

	for (const auto& item : generatorFactory.getRegisteredTypeNames())
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
	ui->randomSeedButton->setEnabled(readyToGenerate);
	ui->runPauseButton->setEnabled(newState != ProgramState::completed);
	ui->width->setEnabled(newState == ProgramState::preparation);
	ui->height->setEnabled(newState == ProgramState::preparation);
	ui->seedEdit->setEnabled(newState == ProgramState::preparation);
	ui->algorithmCombo->setEnabled(newState == ProgramState::preparation);
	ui->imageSaveButton->setEnabled(newState == ProgramState::completed);
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

Mazes::GeneratorContext MazeProgram::getContext()
{
	auto context = Mazes::GeneratorContext();
	context.width = ui->width->value();
	context.height = ui->height->value();
	context.seed = ui->seedEdit->text().toStdString();

	return context;
}

} // namespace Qsd