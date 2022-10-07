#include "QtSfmlDemo/Demos/GridPrinter/GridPrinterDemo.h"

#include <memory>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "Core/Grids/Grid.h"
#include "Core/SfmlTools/Color.h"
#include "QtSfmlDemo/BaseDemo.h"
#include "ui_GridPrinterDemoControls.h"

namespace Visualization
{
GridPrinterDemo::GridPrinterDemo(const Qsd::DemoContext& context)
	: BaseDemo(context)
	, ui(std::make_unique<Ui::GridPrinterDemoControls>())
{
	ui->setupUi(this);

	canvas->setResizingPolicy(QtSfml::ResizingPolicy::keepAspectRato);

	connectControls();
	createGrid();
}

void GridPrinterDemo::run()
{
	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	displayTimer->connect(
		displayTimer, &QTimer::timeout, this, &GridPrinterDemo::update);
	displayTimer->start();
}

auto GridPrinterDemo::getDescription() const -> QString
{
	return "TODO: Add a description later";
}

void GridPrinterDemo::update()
{
	canvas->clear(SfmlTools::Color::grey);
	canvas->draw(gridBoundaries);
	gridPrinter.print(canvas);
	canvas->display();
}

void GridPrinterDemo::connectControls()
{
	auto valueChanged = QOverload<int>::of(&QSpinBox::valueChanged);
	connect(ui->height, valueChanged, this, &GridPrinterDemo::createGrid);
	connect(ui->width, valueChanged, this, &GridPrinterDemo::createGrid);
}

void GridPrinterDemo::createGrid()
{
	grid = Grids::Grid(ui->height->value(), ui->width->value());
	createChessboardPattern();
	gridPrinter.init(grid);

	gridBoundaries = sf::RectangleShape(gridPrinter.getGridArea());
	gridBoundaries.setFillColor(sf::Color::Black);

	canvas->setViewArea(gridPrinter.getGridArea(), gridPrinter.getGridArea() * 0.5f);
}

void GridPrinterDemo::createChessboardPattern()
{
	bool value = false;

	for (auto& row : grid.cells)
	{
		for (auto&& i : row)
		{
			i = value;
			value = !value;
		}

		if (row.size() % 2 == 0)
			value = !value;
	}
}

} // namespace Visualization