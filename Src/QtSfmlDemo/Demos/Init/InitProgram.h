#ifndef __INIT_PROGRAM_H
#define __INIT_PROGRAM_H

#include <QTimer>
#include <SFML/Graphics/CircleShape.hpp>

#include "QtSfml/QtSfmlCanvas.h"

class InitialProgram : public QObject
{
	Q_OBJECT

public:
	InitialProgram();

	void init(QtSfmlCanvas* canvas);
	void run();

private:
	void initTimer();

private slots:
	void update();

private:
	QTimer timer;
	QtSfmlCanvas* canvas;
	sf::CircleShape shape;
};

#endif