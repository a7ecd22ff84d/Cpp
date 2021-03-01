#include "QtSfml/QtSfmlCanvas.h"

#include <iostream>
#include <iterator>
#include <qwidget.h>

QtSfmlCanvas::QtSfmlCanvas(
	QWidget* parent, unsigned int frameTime)
	: QWidget(parent)
	, shape(100)
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
	// Setup the timer
	myTimer.setInterval(frameTime);

	shape.setFillColor(sf::Color::Green);
}

QtSfmlCanvas::~QtSfmlCanvas()
{
}

void QtSfmlCanvas::showEvent(QShowEvent*)
{
	if (!myInitialized)
	{

		// Create the SFML window with the widget handle
		
		// TODO: nie kompiluje się
		// RenderWindow::create((void*)winId());
		// TODO: moja poprawka
		RenderWindow::create(sf::WindowHandle(winId()));

		// Let the derived class do its specific stuff
		OnInit();
		// Setup the timer to trigger a refresh at specified framerate
		connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
		myTimer.start();
		myInitialized = true;
	}
}

QPaintEngine* QtSfmlCanvas::paintEngine() const
{
	return 0;
}

void QtSfmlCanvas::paintEvent(QPaintEvent*)
{
	// Let the derived class do its specific stuff
	OnUpdate();
	// Display on screen

	draw(shape);
	RenderWindow::display();
}

void QtSfmlCanvas::OnInit()
{
}

void QtSfmlCanvas::OnUpdate()
{
}
