#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QTimer>
#include <QWidget>

#include <SFML/Graphics.hpp>
#include <qsize.h>

class QtSfmlCanvas : public QWidget, public sf::RenderWindow
{
	Q_OBJECT
public:
	explicit QtSfmlCanvas(QWidget* parent, unsigned int frameTime = 0);
	virtual ~QtSfmlCanvas();

	virtual void showEvent(QShowEvent*);
	virtual QPaintEngine* paintEngine() const;
	virtual void paintEvent(QPaintEvent*);
	virtual void OnInit();
	virtual void OnUpdate();

    sf::CircleShape shape;

private:
	QTimer myTimer;
	bool myInitialized;
};
#endif // QSMLCANVAS_H