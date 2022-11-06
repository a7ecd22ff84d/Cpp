#pragma once

#include "QtSfml/QtSfmlCanvas.h"

#include <bits/c++config.h>

namespace Visualization::Mazes
{
enum class PrinterUpdate
{
	AfterEachStep,
	AfterFinished
};

class IGeneratorWrapper
{
public:
	virtual void init(
		QtSfmlCanvas& canvas,
		std::size_t height,
		std::size_t width,
		const std::string& seed) = 0;

	virtual auto step(PrinterUpdate update) -> bool = 0;
	virtual void print(QtSfmlCanvas& canvas) const = 0;
};
} // namespace Visualization::Mazes