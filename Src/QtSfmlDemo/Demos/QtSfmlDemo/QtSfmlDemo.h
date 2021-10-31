#ifndef QTSFMLDEMO_H
#define QTSFMLDEMO_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "QtSfmlDemo/BaseDemo.h"

namespace Ui
{
class QtSfmlDemo;
} // namespace Ui

namespace Visualization
{
class QtSfmlDemo : public Qsd::BaseDemo
{
	// NOLINTNEXTLINE
	Q_OBJECT

public:
	explicit QtSfmlDemo(const Qsd::DemoContext& context);
	~QtSfmlDemo() override;

	void run() final;
	[[nodiscard]] auto getDescription() const -> QString final;

private slots:
	void updateViewArea(int x = 0);
	void resetView();

private:
	void initResizeControls();
	void initZoomControls();
	void initViewAreaControls();

	void update();
	void initBackground();
	void initViewAreaBoundaries();

private:
	Ui::QtSfmlDemo* ui;

	std::vector<sf::RectangleShape> background;
	sf::RectangleShape viewAreaBoundaries;
};

} // namespace Visualization

#endif // QTSFMLDEMO_H
