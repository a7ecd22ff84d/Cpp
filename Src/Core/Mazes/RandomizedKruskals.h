#pragma once

#include "Core/Grids/Grid.h"

namespace Core::Mazes
{
class RandomizedKruskals
{
public:
	enum class CellStatus
	{
		NotVisited,
		InGroup,
		Active
	};

	enum class PassageStatus
	{
		NotVisited,
		InGroup,
		Wall
	};

private:
	using Passages = std::vector<Grids::Passage>;

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

public:
	using Maze = Grids::Grid<CellValue, PassageValue, PassageValue>;

	void init(std::size_t height, std::size_t width, const std::string& seed);
	[[nodiscard]] auto getMaze() const -> const Maze&;
	auto step() -> bool;

private:
	void getPassagesInRandomOrder(const std::string& seed);
	void getNextPasaage();
	void createNewGroup();
	void addItemToGroup(unsigned groupId);
	void addSolidWall(unsigned groupId);
	void mergeGroups(unsigned groupId, unsigned groupToMerge);

private:
	Maze maze;

	Passages passages;
	Passages::iterator passagesIt;
	unsigned nextGroupId;
};

} // namespace Core::Mazes
