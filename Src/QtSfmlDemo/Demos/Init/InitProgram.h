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
	InitialProgram(const DemoContext& context);

	virtual void run() final;
	virtual QString getDescription() const final;

private:
	void initTimer();

private slots:
	void update();

private:
	sf::CircleShape shape;
};

} // namespace Qsd

#endif