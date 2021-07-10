#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <memory>

#include "Core/Factory/RegistrableFactory.h"
#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Time/FpsCounter.h"
#include "QtSfml/QtSfmlCanvas.h"
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

namespace Qsd
{
class MazeProgram : public BaseDemo
{
	Q_OBJECT

public:
	MazeProgram(const DemoContext& context);

	~MazeProgram();

	virtual void run() final;
	virtual QString getDescription() const final;

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

	Mazes::GeneratorContext getContext();

private:
	Ui::MazeControls* ui;
	QTimer animationTimer;
	Time::FpsCounter fpsCounter{60, 30};

	MazePrinter printer;
	std::unique_ptr<Mazes::IMazeGenerator> generator;
	ProgramState state;

	Factory::RegistrableFactory<Mazes::IMazeGenerator> generatorFactory;
	unsigned steps = 0;
};

} // namespace Qsd

#endif