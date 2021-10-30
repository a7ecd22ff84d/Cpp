#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QTimer>
#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace QtSfml
{
enum class ResizingPolicy
{
	keepAspectRato = 0,
	keepZoomLevel,
	stretch
};

Q_NAMESPACE
Q_ENUM_NS(ResizingPolicy) // NOLINT

} // namespace QtSfml

class QtSfmlCanvas : public QWidget, public sf::RenderWindow
{
	// NOLINTNEXTLINE
	Q_OBJECT
public:
	explicit QtSfmlCanvas(QWidget* parent);
	~QtSfmlCanvas() override = default;

	void showEvent(QShowEvent*) override;
	auto paintEngine() const -> QPaintEngine* override;
	void resizeEvent(QResizeEvent* event) override;

	void setResizingPolicy(QtSfml::ResizingPolicy policy);
	void setViewArea(sf::Vector2f center, sf::Vector2f size);
	void refreshViewArea();

	auto getZoomLevel() -> float;
	void setZoomLevel(float zoom);

private:
	auto calculateViewAreaKeepingAspectRatio(sf::Vector2f size) -> sf::Vector2f;

private:
	QtSfml::ResizingPolicy resizingPolicy = QtSfml::ResizingPolicy::keepAspectRato;
	sf::Vector2f viewArea;
	float zoom = 1;
	sf::Vector2f centerPoint;
};

#endif // QSMLCANVAS_H