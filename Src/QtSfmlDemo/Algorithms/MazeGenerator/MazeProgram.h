#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <QObject>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeGenerator.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

namespace Ui
{
class MazeControls;
}

class MazeProgram : public QObject
{
	Q_OBJECT

public:
	MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer);
	void connectTimers();
	void connectControls();
	void run();

private slots:
	void update();
	void nextStep();
	void toogleAnimation();

private:
	void initMaze();

private:
	QtSfmlCanvas* canvas;
	Ui::MazeControls* ui;
	QTimer* displayTimer;
	QTimer animationTimer;

	MazePrinter printer;
	MazeGenerator generator;
};

#endif