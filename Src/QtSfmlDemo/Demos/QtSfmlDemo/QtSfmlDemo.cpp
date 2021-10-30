#include "QtSfmlDemo.h"

#include "ui_QtSfmlDemo.h"

namespace Visualization
{
QtSfmlDemo::QtSfmlDemo(const Qsd::DemoContext& context)
	: BaseDemo(context)
	, ui(new Ui::QtSfmlDemo)
{
	ui->setupUi(this);

	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	connect(displayTimer, &QTimer::timeout, this, &QtSfmlDemo::update);
}

QtSfmlDemo::~QtSfmlDemo()
{
	delete ui;
}

void QtSfmlDemo::run()
{
	displayTimer->start();
}

auto QtSfmlDemo::getDescription() const -> QString
{
	return "";
}

void QtSfmlDemo::update()
{
	canvas->clear();
	canvas->display();
}

} // namespace Visualization