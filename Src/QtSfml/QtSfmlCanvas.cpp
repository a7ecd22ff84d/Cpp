#include "QtSfml/QtSfmlCanvas.h"

#include <iostream>
#include <string_view>

#include <QResizeEvent>
#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <fmt/core.h>

namespace
{
void log(std::string_view msg)
{
	// std::cout << msg;
}

} // namespace

QtSfmlCanvas::QtSfmlCanvas(QWidget* parent) : QWidget(parent)
{
	// Setup some states to allow direct rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	// Set strong focus to enable keyboard events to be received
	setFocusPolicy(Qt::StrongFocus);
}

QtSfmlCanvas::~QtSfmlCanvas()
{
}

void QtSfmlCanvas::showEvent(QShowEvent*)
{
	RenderWindow::create(sf::WindowHandle(winId()));
}

QPaintEngine* QtSfmlCanvas::paintEngine() const
{
	return 0;
}

void QtSfmlCanvas::resizeEvent(QResizeEvent* event)
{
	auto width = static_cast<float>(event->size().width());
	auto height = static_cast<float>(event->size().height());
	auto newSize = sf::Vector2f(width, height);

	log(fmt::format("Widget resized to [{},{}]\n", width, height));

	sf::RenderWindow::setSize(sf::Vector2u(width, height));

	if (resizingPolicy == ResizingPolicy::keepZoomLevel)
		setView({centerPoint, newSize});
	else if (resizingPolicy == ResizingPolicy::keepAspectRato)
		setView({centerPoint, calculateViewAreaKeepingAspectRatio(newSize)});
	else if (resizingPolicy == ResizingPolicy::stretch)
		setView(sf::View(centerPoint, viewArea));
}

void QtSfmlCanvas::setViewArea(sf::Vector2f viewArea, sf::Vector2f center)
{
	log(fmt::format(
		"View area set to [{},{}], center in [{},{}]\n",
		viewArea.x,
		viewArea.y,
		center.x,
		center.y));

	this->viewArea = viewArea;
	centerPoint = center;

	auto rs = QResizeEvent(QWidget::size(), QSize(0, 0));
	resizeEvent(&rs);
}

sf::Vector2f QtSfmlCanvas::calculateViewAreaKeepingAspectRatio(sf::Vector2f size)
{
	auto zoom = std::max(viewArea.x / size.x, viewArea.y / size.y);
	auto visibleArea = size * zoom;

	log(fmt::format(
		"Calculated visible area [{},{}]\n", visibleArea.x, visibleArea.y));

	return visibleArea;
}