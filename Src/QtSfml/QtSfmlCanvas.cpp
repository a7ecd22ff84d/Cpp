#include "QtSfml/QtSfmlCanvas.h"

#include <iostream>
#include <iterator>

#include <QResizeEvent>
#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>
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

		initialAspectRatio = double(getSize().x) / getSize().y;
	}
}

void QtSfmlCanvas::resizeEvent(QResizeEvent* event)
{
	if (resizingPolicy == ResizingPolicy::keepZoomLevel)
		return;

	auto width = event->size().width();
	auto height = event->size().height();
	sf::Vector2u canvasSize;

	if (resizingPolicy == ResizingPolicy::stretch)
	{
		canvasSize = sf::Vector2u(width, height);
	}
	else if (resizingPolicy == ResizingPolicy::keepAspectRato)
	{
		double aspectRatio = double(width) / height;

		if (aspectRatio < initialAspectRatio)
			canvasSize = sf::Vector2u(width, width / initialAspectRatio);
		else
			canvasSize = sf::Vector2u(height * initialAspectRatio, height);
	}

	sf::RenderWindow::setSize(canvasSize);
}

QPaintEngine* QtSfmlCanvas::paintEngine() const
{
	return 0;
}
