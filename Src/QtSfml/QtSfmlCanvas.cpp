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

using QtSfml::ResizingPolicy;

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

void QtSfmlCanvas::showEvent(QShowEvent*)
{
	RenderWindow::create(sf::WindowHandle(winId()));
	refreshViewArea();
}

auto QtSfmlCanvas::paintEngine() const -> QPaintEngine*
{
	return nullptr;
}

void QtSfmlCanvas::resizeEvent(QResizeEvent* event)
{
	auto width = static_cast<float>(event->size().width());
	auto height = static_cast<float>(event->size().height());
	auto newSize = sf::Vector2f(width, height);

	log(fmt::format("Widget resized to [{},{}]\n", width, height));

	sf::RenderWindow::setSize(sf::Vector2u(width, height));
	sf::Vector2f currentViewArea;

	if (resizingPolicy == ResizingPolicy::keepZoomLevel)
		currentViewArea = newSize;
	else if (resizingPolicy == ResizingPolicy::keepAspectRato)
		currentViewArea = calculateViewAreaKeepingAspectRatio(newSize);
	else if (resizingPolicy == ResizingPolicy::stretch)
		currentViewArea = viewArea;

	setView({centerPoint, currentViewArea / zoom});
}

void QtSfmlCanvas::setResizingPolicy(ResizingPolicy policy)
{
	resizingPolicy = policy;
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

	refreshViewArea();
}

void QtSfmlCanvas::refreshViewArea()
{
	auto rs = QResizeEvent(QWidget::size(), QSize(0, 0));
	resizeEvent(&rs);
}

auto QtSfmlCanvas::getZoomLevel() -> float
{
	return zoom;
}

void QtSfmlCanvas::setZoomLevel(float zoom)
{
	this->zoom = zoom;
	refreshViewArea();
}

auto QtSfmlCanvas::calculateViewAreaKeepingAspectRatio(sf::Vector2f size)
	-> sf::Vector2f
{
	auto visibleArea = size * std::max(viewArea.x / size.x, viewArea.y / size.y);

	log(fmt::format(
		"Calculated visible area [{},{}]\n", visibleArea.x, visibleArea.y));

	return visibleArea;
}