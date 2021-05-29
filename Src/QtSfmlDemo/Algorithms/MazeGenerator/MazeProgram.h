#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <memory>

#include <QWidget>
#include <QStatusBar>

#include "Core/Mazes/GeneratorFactory.h"
#include "Core/Mazes/IMazeGenerator.h"
#include "Core/Time/FpsCounter.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

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

class MazeProgram : public QWidget
{
	Q_OBJECT

public:
	MazeProgram(
		QtSfmlCanvas* canvas,
		QWidget* controlsWidget,
		QStatusBar* statusBar,
		QTimer* timer);

	~MazeProgram();

	void run();

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
	QtSfmlCanvas* canvas;
	QStatusBar* statusBar;
	Ui::MazeControls* ui;
	QTimer* displayTimer;
	QTimer animationTimer;
	Time::FpsCounter fpsCounter{60,30};

	MazePrinter printer;
	std::unique_ptr<Mazes::IMazeGenerator> generator;
	ProgramState state;

	Mazes::GeneratorFactory generatorFactory;
	unsigned steps = 0;
};

#endif