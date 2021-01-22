#include <QPainter>
#include <iostream>

#include <QtSfml/SfmlWindow.h>
#include <SFML/Graphics/RenderWindow.hpp>

SfmlWindow::SfmlWindow(QQuickItem* parent)
{
}

QString SfmlWindow::name() const
{
	return m_name;
}

void SfmlWindow::setName(const QString& name)
{
	m_name = name;
}

QColor SfmlWindow::color() const
{
	return m_color;
}

void SfmlWindow::setColor(const QColor& color)
{
	m_color = color;
}

void SfmlWindow::paint(QPainter* painter)
{
	std::cout << "paining" << std::endl;

	sf::RenderWindow::setPosition({100, 100});
	sf::RenderWindow::setSize({100, 100});

	sf::RenderWindow::display();

	// window = std::make_unique<sf::RenderWindow>(
	// 	sf::VideoMode(width(), height()), "asdsa", sf::Style::None);

	QRectF rectangle(x(), y(), width() - 1, height() - 1);
	painter->drawRect(rectangle);


	// auto globalPosition = mapToGlobal({x(), y()});

	// window->setPosition(
	// 	{static_cast<int>(globalPosition.x()),
	// 	 static_cast<int>(globalPosition.y())});
	// window->display();
}