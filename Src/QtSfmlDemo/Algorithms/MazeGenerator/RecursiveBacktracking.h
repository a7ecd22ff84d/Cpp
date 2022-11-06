#pragma once

#include "Core/Mazes/RecursiveBacktrackingGenerator.h"
#include "QtSfml/QtSfmlCanvas.h"
#include "QtSfmlDemo/Algorithms/MazeGenerator/IGeneratorWrapper.h"
#include "QtSfmlDemo/Common/GridPrinter.h"

#include <bits/c++config.h>

namespace Visualization::Mazes
{
class RecursiveBacktracking : public IGeneratorWrapper
{
	using Maze = Core::Mazes::RecursiveBacktrackingGenerator::Maze;

public:
	void init(
		QtSfmlCanvas& canvas,
		std::size_t height,
		std::size_t width,
		const std::string& seed) override;
	auto step(PrinterUpdate update) -> bool override;
	void print(QtSfmlCanvas& canvas) const override;

private:
	Core::Mazes::RecursiveBacktrackingGenerator generator;
	Visualization::GridPrinter<Maze> printer;
};

} // namespace Visualization::Mazes