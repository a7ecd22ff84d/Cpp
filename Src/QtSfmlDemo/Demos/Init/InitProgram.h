#ifndef __INIT_PROGRAM_H
#define __INIT_PROGRAM_H

#include <SFML/Graphics/CircleShape.hpp>

#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/BaseDemo.h"

namespace Qsd
{
class InitialProgram : public BaseDemo
{
	Q_OBJECT

public:
	InitialProgram(
		QWidget* controlsWidget,
		QtSfmlCanvas* canvas,
		QStatusBar* statusBar,
		QTimer* timer);

	virtual void run() final;

private:
	void initTimer();

private slots:
	void update();

private:
	sf::CircleShape shape;
};

} // namespace Qsd

#endif