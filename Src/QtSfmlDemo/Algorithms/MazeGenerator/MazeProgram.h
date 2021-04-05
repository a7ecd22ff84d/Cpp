#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <memory>
#include <QObject>

#include "Core/Generator/Maze/IMazeGenerator.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeGeneratorFactory.h"
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

class MazeProgram : public QObject
{
	Q_OBJECT

public:
	MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer);

	void run();

private slots:
	void reset();
	void update();
	void algorithmChanged(int index);
	void nextStep();
	void toogleAnimation();
	void generateAll();

private:
	void connectTimers();
	void connectControls();
	void registerGenerators();
	void updateState(ProgramState newState);
	void setAnimationEnabled(bool enabled);

	GeneratorContext getContext();

private:
	QtSfmlCanvas* canvas;
	Ui::MazeControls* ui;
	QTimer* displayTimer;
	QTimer animationTimer;

	MazePrinter printer;
	std::unique_ptr<IMazeGenerator> generator;
	ProgramState state;

	MazeGeneratorFactory generatorFactory;
};

#endif