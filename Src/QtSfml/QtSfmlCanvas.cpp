#include "QtSfml/QtSfmlCanvas.h"

#include <iostream>
#include <iterator>
#include <ostream>

#include <QResizeEvent>
#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

QtSfmlCanvas::QtSfmlCanvas(QWidget* parent) : QWidget(parent)
{
	// Setup some states to allow direct rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	// Set strong focus to enable keyboard events to be received
	setFocusPolicy(Qt::StrongFocus);
	// Setup the widget geometry
	move(parent->pos());
	resize(parent->size());
}

QtSfmlCanvas::~QtSfmlCanvas()
{
}

void QtSfmlCanvas::showEvent(QShowEvent*)
{
	if (!myInitialized)
	{
		RenderWindow::create(sf::WindowHandle(winId()));
		myInitialized = true;

		initialSize = {
			static_cast<float>(getSize().x), static_cast<float>(getSize().y)};
		centerPoint = {initialSize.x / 2, initialSize.y / 2};
	}
}

void QtSfmlCanvas::resizeEvent(QResizeEvent* event)
{
	auto width = static_cast<float>(event->size().width());
	auto height = static_cast<float>(event->size().height());

	if (resizingPolicy == ResizingPolicy::keepZoomLevel)
	{
		setView({centerPoint, {width, height}});
	}
	else if (resizingPolicy == ResizingPolicy::keepAspectRato)
	{
		auto newView = sf::View(centerPoint, {width, height});
		newView.zoom(std::max(initialSize.x / width, initialSize.y / height));
		setView(sf::View(newView));
	}
	else if (resizingPolicy == ResizingPolicy::stretch)
	{
		setView(sf::View(centerPoint, initialSize));
	}

	sf::RenderWindow::setSize(sf::Vector2u(width, height));
}

QPaintEngine* QtSfmlCanvas::paintEngine() const
{
	return 0;
}
