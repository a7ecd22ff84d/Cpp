#ifndef __MAZE_PROGRAM_H
#define __MAZE_PROGRAM_H

#include <QObject>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

class MazeProgram : public QObject
{
	Q_OBJECT

public:
	MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer);
	void connectTimer();
	void run();

private slots:
	void update();

private:
	QtSfmlCanvas* canvas;
	QWidget* controlsWidget;
	QTimer* timer;

	MazePrinter printer;
};

#endif