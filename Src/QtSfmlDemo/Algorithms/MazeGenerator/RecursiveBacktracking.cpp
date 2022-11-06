#include "QtSfmlDemo/Algorithms/MazeGenerator/RecursiveBacktracking.h"

#include <SFML/Graphics/Color.hpp>

#include "Core/Mazes/RecursiveBacktrackingGenerator.h"
#include "Core/SfmlTools/Color.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/IGeneratorWrapper.h"

namespace Visualization::Mazes
{
void RecursiveBacktracking::init(
	QtSfmlCanvas& canvas, std::size_t height, std::size_t width, const std::string& seed)
{
	auto cellPainter = [](Maze::CellValueType value, sf::RectangleShape& rect) {
		switch (value)
		{
		case Maze::CellValueType::NotVisited:
			rect.setFillColor(SfmlTools::Color::grey);
			break;
		case Maze::CellValueType::InStack:
			rect.setFillColor(SfmlTools::Color::darkRed);
			break;
		case Maze::CellValueType::Visited:
			rect.setFillColor(sf::Color::Red);
			break;
		case Maze::CellValueType::Active:
			rect.setFillColor(SfmlTools::Color::darkBlue);
			break;
		}
	};

	auto passagePainter = [](Maze::EastPassageValueType value,
							 sf::RectangleShape& rect) {
		switch (value)
		{
		case Maze::EastPassageValueType::NotVisited:
			rect.setFillColor(sf::Color::Black);
			break;
		case Maze::EastPassageValueType::InStack:
			rect.setFillColor(SfmlTools::Color::darkRed);
			break;
		case Maze::EastPassageValueType::Visited:
			rect.setFillColor(sf::Color::Red);
			break;
		}
	};

	Visualization::GridPrinterParams<Maze> params;
	params.cellSize = 10;
	params.passageWidth = 2;
	params.cellPainter = cellPainter;
	params.epPainter = passagePainter;
	params.spPainter = passagePainter;

	generator.initNewMaze(height, width, seed);
	printer.init(generator.getMaze(), params);

	canvas.setViewArea(printer.getGridArea(), printer.getGridArea() * 0.5f);
}

auto RecursiveBacktracking::step(PrinterUpdate update) -> bool
{
	auto inProgress = generator.step();

	if (update == PrinterUpdate::AfterEachStep
		or (update == PrinterUpdate::AfterFinished and not inProgress))
	{
		printer.update(generator.getMaze());
	}

	return inProgress;
}

void RecursiveBacktracking::print(QtSfmlCanvas& canvas) const
{
	printer.print(canvas);
}

} // namespace Visualization::Mazes