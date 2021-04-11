#include "QtSfml/QtSfmlCanvas.h"

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
	this->viewArea = viewArea;
	centerPoint = center;

	auto rs = QResizeEvent(QWidget::size(), QSize(0, 0));
	resizeEvent(&rs);
}

sf::Vector2f QtSfmlCanvas::calculateViewAreaKeepingAspectRatio(sf::Vector2f size)
{
	auto zoom = std::max(viewArea.x / size.x, viewArea.y / size.y);
	return size * zoom;
}