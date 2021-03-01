#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QTimer>
#include <QWidget>

#include <SFML/Graphics/RenderWindow.hpp>

class QtSfmlCanvas : public QWidget, public sf::RenderWindow
{
	Q_OBJECT
public:
	explicit QtSfmlCanvas(QWidget* parent, unsigned int frameTime = 0);
	~QtSfmlCanvas();

	virtual void showEvent(QShowEvent*);
	virtual QPaintEngine* paintEngine() const;

private:
	bool myInitialized;
};
#endif // QSMLCANVAS_H