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
	void connectTimer();
	void connectControls();
	void run();

private slots:
	void update();
	void nextStep();

private:
	void initMaze();

private:
	QtSfmlCanvas* canvas;
	// QWidget* controlsWidget;
	QTimer* timer;
	Ui::MazeControls* ui;

	Maze maze;
	MazePrinter printer;
	MazeGenerator generator;
};

#endif