#pragma once

#include <stack>
#include <string>

#include "Core/Grids/Grid.h"
#include "Core/Mazes/Maze.h"
#include "Core/Random/VariableRangeRng.h"

namespace Core::Mazes
{
class RecursiveBacktrackingGenerator
{
	struct Coordinates
	{
		unsigned column;
		unsigned row;
	};

	using Cells = std::vector<Coordinates>;

	enum class CellValue
	{
		NotVisited,
		InStack,
		Visited,
		Active
	};

	enum class PassageValue
	{
		NotVisited,
		InStack,
		Visited
	};

public:
	using Maze = Grids::Grid<CellValue, PassageValue, PassageValue>;

	void initNewMaze(std::size_t height, std::size_t width, const std::string& seed);
	auto step() -> bool;

	[[nodiscard]] auto getMaze() const -> const Maze&;

private:
	[[nodiscard]] auto getAdjacentCells(Coordinates coordinates) const -> Cells;
	void removeVisitedCells(Cells& cells) const;
	auto getNextCell(const Cells& availableCells) -> Coordinates;
	void setCellStatus(Coordinates coordinates, Maze::CellValueType status);

private:
	Maze maze;
	std::string seed;

	std::stack<Coordinates> stack;
	VariableRangeRng rng;
};

} // namespace Core::Mazes