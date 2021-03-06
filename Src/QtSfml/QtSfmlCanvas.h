#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QTimer>
#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

enum class ResizingPolicy
{
	keepAspectRato,
	keepZoomLevel,
	stretch
};

class QtSfmlCanvas : public QWidget, public sf::RenderWindow
{
	Q_OBJECT
public:
	explicit QtSfmlCanvas(QWidget* parent);
	~QtSfmlCanvas();

	virtual void showEvent(QShowEvent*);
	virtual QPaintEngine* paintEngine() const;
	virtual void resizeEvent(QResizeEvent* event);

	void setViewArea(sf::Vector2f center, sf::Vector2f size);

private:
	sf::Vector2f calculateViewAreaKeepingAspectRatio(sf::Vector2f size);

private:
	ResizingPolicy resizingPolicy = ResizingPolicy::keepAspectRato;
	sf::Vector2f viewArea;
	sf::Vector2f centerPoint;
};
#endif // QSMLCANVAS_H