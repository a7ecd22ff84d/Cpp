#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeProgram.h"

#include "QtSfmlDemo/Algorithms/MazeGenerator/MazeControls.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/MazePrinter.h"

MazeProgram::MazeProgram(QtSfmlCanvas* canvas, QWidget* controlsWidget, QTimer* timer)
	: canvas(canvas)
	, controlsWidget(new MazeControls(controlsWidget))
	, timer(timer)
	, printer(MazePrinter(canvas))
{
	connectTimer();
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

void MazeProgram::update()
{
	printer.draw();
}
