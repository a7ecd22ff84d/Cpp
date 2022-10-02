#include "QtSfmlDemo/Demos/GridPrinter/GridPrinterDemo.h"

#include <SFML/Graphics/Color.hpp>

#include "Core/SfmlTools/Color.h"
#include "QtSfmlDemo/BaseDemo.h"

namespace Visualization
{
GridPrinterDemo::GridPrinterDemo(const Qsd::DemoContext& context)
	: BaseDemo(context)
	, grid(10, 20)
{
	// init example maze
	bool value = false;

	for (auto& row : grid.cells)
	{
		if (row.size() % 2 == 0)
			value = !value;

		for (auto&& i : row)
		{
			i = value;
			value = !value;
		}
	}

	gridPrinter.init(grid);

	const auto viewSizeHeight = 10.0f * grid.height();
	const auto viewSizewidth = 10.0f * grid.width();
	gridBoundaries = sf::RectangleShape({viewSizewidth, viewSizeHeight});
	gridBoundaries.setFillColor(sf::Color::Black);

	canvas->setViewArea(
		{viewSizewidth, viewSizeHeight + 1},
		{viewSizewidth / 2, viewSizeHeight / 2});
	canvas->setResizingPolicy(QtSfml::ResizingPolicy::keepAspectRato);
}

void GridPrinterDemo::run()
{
	displayTimer->setInterval(std::chrono::milliseconds(1000 / 60));
	displayTimer->connect(displayTimer, SIGNAL(timeout()), this, SLOT(update()));
	displayTimer->start();
}

auto GridPrinterDemo::getDescription() const -> QString
{
	return "TODO: Add description later";
}

void GridPrinterDemo::update()
{
	canvas->clear(SfmlTools::Color::grey);
	canvas->draw(gridBoundaries);
	gridPrinter.print(canvas);
	canvas->display();
}

} // namespace Visualization