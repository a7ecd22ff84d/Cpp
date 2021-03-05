#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QTimer>
#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

enum class ResizingPolicy
{
	stretch,
	keepAspectRato,
	keepZoomLevel
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

private:
	ResizingPolicy resizingPolicy = ResizingPolicy::keepZoomLevel;
	bool myInitialized = false;
	double initialAspectRatio;
};
#endif // QSMLCANVAS_H