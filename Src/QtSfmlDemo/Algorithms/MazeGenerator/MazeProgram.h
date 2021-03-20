#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <QObject>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"

class MazeProgram : public QObject
{
	Q_OBJECT

public:
	MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer);
	void connectTimer();
	void run();

private:
	void initMaze();

private slots:
	void update();

private:
	QtSfmlCanvas* canvas;
	QWidget* controlsWidget;
	QTimer* timer;
	Maze maze;

	MazePrinter printer;
};

#endif