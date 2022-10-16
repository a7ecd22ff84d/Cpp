#pragma once

#include <memory>

#include "Core/Grids/Grid.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/BaseDemo.h"
#include "QtSfmlDemo/Common/GridPrinter.h"
#include "ui_GridPrinterDemoControls.h"

namespace Ui
{
class GridPrinterDemoControls;
} // namespace Ui

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
	void update();
	void connectControls();

	void createGrid();
	void createChessboardPattern(bool createPassages);

private:
	Grids::Grid<bool> grid;
	GridPrinter gridPrinter;
	sf::RectangleShape gridBoundaries;
	std::unique_ptr<Ui::GridPrinterDemoControls> ui;
};

} // namespace Visualization
