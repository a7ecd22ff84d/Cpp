#pragma once

#include <optional>
#include <set>

#include "Core/Grids/Grid.h"

namespace Core::Mazes
{
class RandomizedKruskals
{
public:
	enum class CellStatus
	{
		NotVisited,
		Visited,
		Active
	};

	enum class PassageStatus
	{
		NotVisited,
		InGroup,
		Wall
	};

private:
	struct Coordinates
	{
		unsigned column;
		unsigned row;
	};

	using Cells = std::vector<Coordinates>;

	struct CellValue
	{
		CellStatus status;
		unsigned groupId;
	};

	struct PassageValue
	{
		PassageStatus status;
		unsigned groupId;
	};

	using Passage = std::pair<Coordinates, Coordinates>;
	using Passages = std::vector<Passage>;

public:
	using Maze = Grids::Grid<CellValue, PassageValue, PassageValue>;

	void init(std::size_t height, std::size_t width, const std::string& seed);
	[[nodiscard]] auto getMaze() const -> const Maze&;
	auto step() -> bool;

private:
	void getPassagesInRandomOrder(const std::string& seed);

private:
	Maze maze;

	Passages passages;
	Passages::iterator passagesIt;
	std::optional<Passage> activePassage;
	unsigned nextGroupId;
};

} // namespace Core::Mazes
