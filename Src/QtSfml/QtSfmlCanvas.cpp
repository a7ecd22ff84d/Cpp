#include "QtSfml/QtSfmlCanvas.h"

#include <iostream>
#include <iterator>

#include <qwidget.h>

QtSfmlCanvas::QtSfmlCanvas(QWidget* parent, unsigned int frameTime)
	: QWidget(parent)

	, myInitialized(false)
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
	}
}

QPaintEngine* QtSfmlCanvas::paintEngine() const
{
	return 0;
}
