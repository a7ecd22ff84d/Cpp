#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <QObject>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeGenerator.h"
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
	void nextStep();
	void toogleAnimation();

private:
	void connectTimers();
	void connectControls();
	void updateState(ProgramState newState);
	void setAnimationEnabled(bool enabled);

private:
	QtSfmlCanvas* canvas;
	Ui::MazeControls* ui;
	QTimer* displayTimer;
	QTimer animationTimer;

	MazePrinter printer;
	MazeGenerator generator;
	ProgramState state;
};

#endif