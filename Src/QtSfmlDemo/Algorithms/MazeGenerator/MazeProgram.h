#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <memory>

#include "Core/Factory/RegistrableFactory.h"
#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Time/FpsCounter.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/IGeneratorWrapper.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"
#include "QtSfmlDemo/BaseDemo.h"
#include "QtSfmlDemo/DemoContext.h"

enum class ProgramState
{
	preparation,
	generation,
	animation,
	completed,
};

namespace Ui
{
class MazeControls;
} // namespace Ui

namespace Visualization::Mazes
{
class MazeProgram : public Qsd::BaseDemo
{
	// NOLINTNEXTLINE
	Q_OBJECT

public:
	MazeProgram(const Qsd::DemoContext& context);

	void run() final;
	[[nodiscard]] auto getDescription() const -> QString final;

private slots:
	void reset();
	void update();
	void algorithmChanged(int index);
	void nextStep();
	void toggleAnimation();
	void generateAll();
	void saveImage();
	void generateSeed();

private:
	void connectTimers();
	void connectControls();
	void registerGenerators();
	void updateState(ProgramState newState);
	void setAnimationEnabled(bool enabled);

private:
	std::shared_ptr<Ui::MazeControls> ui;
	QTimer animationTimer;
	Time::FpsCounter fpsCounter{60, 30};

	std::unique_ptr<IGeneratorWrapper> generatorWrapper;
	Factory::RegistrableFactory<IGeneratorWrapper> generatorFactory;

	ProgramState state;
	unsigned steps = 0;
};

} // namespace Visualization::Mazes

#endif