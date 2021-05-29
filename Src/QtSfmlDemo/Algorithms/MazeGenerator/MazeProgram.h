#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <memory>

#include "Core/Mazes/GeneratorFactory.h"
#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Time/FpsCounter.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"
#include "QtSfmlDemo/BaseDemo.h"

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
	MazeProgram(
		QWidget* controlsWidget,
		QtSfmlCanvas* canvas,
		QStatusBar* statusBar,
		QTimer* timer);

	~MazeProgram();

	virtual void run() final;

private slots:
	void reset();
	void update();
	void algorithmChanged(int index);
	void nextStep();
	void toogleAnimation();
	void generateAll();
	void saveImage();

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

	Mazes::GeneratorFactory generatorFactory;
	unsigned steps = 0;
};

} // namespace Qsd

#endif