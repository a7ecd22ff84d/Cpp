#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include "QtSfmlDemo/Algorithms/MazeGenerator/Maze.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeControls.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

MazeProgram::MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer)
	: canvas(canvas)
	, controlsWidget(new MazeControls(controlsWidget))
	, timer(timer)
	, printer(MazePrinter(canvas))
{
	connectTimer();
	initMaze();
	printer.updateMaze(maze);
}

void MazeProgram::connectTimer()
{
	timer->setInterval(std::chrono::milliseconds(1000 / 60));
	timer->connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void MazeProgram::run()
{
	timer->start();
}

void MazeProgram::initMaze()
{
	maze.emplace_back(Passage({0,0}, {0,1}));
	maze.emplace_back(Passage({1,0}, {0,0}));
	maze.emplace_back(Passage({1,1}, {0,1}));
	maze.emplace_back(Passage({1,2}, {1,1}));
	maze.emplace_back(Passage({1,3}, {1,2}));
	maze.emplace_back(Passage({2,3}, {2,2}));
}

void MazeProgram::update()
{
	printer.draw();
}
