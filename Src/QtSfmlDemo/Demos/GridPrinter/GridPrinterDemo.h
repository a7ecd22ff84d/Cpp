#pragma once

#include "Core/Grids/Grid.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/BaseDemo.h"
#include "QtSfmlDemo/Common/GridPrinter.h"

namespace Visualization
{
class GridPrinterDemo : public Qsd::BaseDemo
{
	// NOLINTNEXTLINE
	Q_OBJECT

public:
	GridPrinterDemo(const Qsd::DemoContext& context);

	void run() final;
	[[nodiscard]] auto getDescription() const -> QString final;

private:
	void initTimer();

private slots:
	void update();

private:
	Grids::Grid grid;
	GridPrinter gridPrinter;
	sf::RectangleShape gridBoundaries;
};

} // namespace Visualization
