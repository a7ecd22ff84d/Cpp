
#include <QColor>
#include <QtQml>

#include <QtQuick/QQuickPaintedItem>
#include <SFML/Graphics/RenderWindow.hpp>

class SfmlWindow : public QQuickPaintedItem, public sf::RenderWindow
{
	Q_OBJECT
	Q_PROPERTY(QString name READ name WRITE setName)
	Q_PROPERTY(QColor color READ color WRITE setColor)
	// QML_ELEMENT

public:
	SfmlWindow(QQuickItem* parent = 0);

	QString name() const;
	void setName(const QString& name);

	QColor color() const;
	void setColor(const QColor& color);

	void paint(QPainter* painter);

private:
	QString m_name;
	QColor m_color;
};