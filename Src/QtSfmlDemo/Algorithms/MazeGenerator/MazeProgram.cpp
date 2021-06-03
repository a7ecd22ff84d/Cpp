#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include <filesystem>
#include <memory>
#include <string_view>

#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QWidget>
#include <fmt/core.h>

#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Mazes/Maze.h"
#include "Core/Mazes/RandomizedKruskals.h"
#include "Core/Mazes/RecursiveBacktrackingGenerator.h"
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

	show(); // ten show jest wymagany tylko i wyłącznie jeśli przełączamy się
			// między programami. Jeśli program jest wybrany jako pierwszt to
			// wszystko magicznie działa bez tego show

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
		steps++;

	printer.updateMaze(generator->getMaze());
	updateState(ProgramState::completed);
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

	if (std::find(availableExtensions.begin(), availableExtensions.end(), extension)
		== availableExtensions.end())
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