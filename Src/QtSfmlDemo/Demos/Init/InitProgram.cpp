#include "QtSfmlDemo/Demos/Init/InitProgram.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "QtSfmlDemo/BaseDemo.h"

namespace Qsd
{
InitialProgram::InitialProgram(const DemoContext& context)
	: BaseDemo(context)
	, shape(20)
{
}

void InitialProgram::run()
{
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);

	canvas->clear();
	canvas->draw(shape);
	canvas->display();

	initTimer();
	displayTimer->start();
}

QString InitialProgram::getDescription() const
{
	return "Simple test program, nothin interesting here.";
}

void InitialProgram::initTimer()
{
	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	displayTimer->connect(displayTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void InitialProgram::update()
{
	canvas->clear();
	canvas->draw(shape);
	canvas->display();
}

} // namespace Qsd