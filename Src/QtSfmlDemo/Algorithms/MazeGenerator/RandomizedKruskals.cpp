#include "Core/Mazes/RandomizedKruskals.h"

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Core/SfmlTools/Color.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/IGeneratorWrapper.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/RandomizedKruskals.h"

namespace
{
auto groupIdToColor(unsigned groupId) -> sf::Color
{
	return {
		static_cast<sf::Uint8>((groupId * 70) % 150 + 100),
		static_cast<sf::Uint8>((groupId * 120) % 150 + 100),
		static_cast<sf::Uint8>((groupId * 145) % 150 + 100)};
}
} // namespace

namespace Visualization::Mazes
{
void RandomizedKruskals::init(
	QtSfmlCanvas& canvas, std::size_t height, std::size_t width, const std::string& seed)
{
	auto cellPainter = [](Maze::CellValueType value, sf::RectangleShape& rect) {
		switch (value.status)
		{
		case Core::Mazes::RandomizedKruskals::CellStatus::NotVisited:
			rect.setFillColor(SfmlTools::Color::grey);
			break;
		case Core::Mazes::RandomizedKruskals::CellStatus::InGroup:
			rect.setFillColor(groupIdToColor(value.groupId));
			break;
		case Core::Mazes::RandomizedKruskals::CellStatus::Active:
			rect.setFillColor(SfmlTools::Color::darkBlue);
			break;
		}
	};

	auto passagePainter = [](Maze::EastPassageValueType value,
							 sf::RectangleShape& rect) {
		switch (value.status)
		{
		case Core::Mazes::RandomizedKruskals::PassageStatus::NotVisited:
			rect.setFillColor(SfmlTools::Color::lightGrey);
			break;
		case Core::Mazes::RandomizedKruskals::PassageStatus::InGroup:
			rect.setFillColor(groupIdToColor(value.groupId));
			break;
		case Core::Mazes::RandomizedKruskals::PassageStatus::Wall:
			rect.setFillColor(sf::Color::Black);
			break;
		}
	};

	Visualization::GridPrinterParams<Maze> params;
	params.cellSize = 10;
	params.passageWidth = 2;
	params.cellPainter = cellPainter;
	params.epPainter = passagePainter;
	params.spPainter = passagePainter;

	generator.init(height, width, seed);
	printer.init(generator.getMaze(), params);

	canvas.setViewArea(printer.getGridArea(), printer.getGridArea() * 0.5f);
}

auto RandomizedKruskals::step(PrinterUpdate update) -> bool
{
	auto inProgress = generator.step();

	if (update == PrinterUpdate::AfterEachStep
		or (update == PrinterUpdate::AfterFinished and not inProgress))
	{
		printer.update(generator.getMaze());
	}

	return inProgress;
}

void RandomizedKruskals::print(QtSfmlCanvas& canvas) const
{
	printer.print(canvas);
}

} // namespace Visualization::Mazes