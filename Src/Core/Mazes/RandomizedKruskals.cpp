#include "Core/Mazes/RandomizedKruskals.h"

#include <algorithm>
#include <optional>
#include <utility>

#include "Core/Mazes/BaseGenerator.h"
#include "Core/Mazes/Maze.h"
#include "fmt/core.h"

namespace Core::Mazes
{
void RandomizedKruskals::init(
	std::size_t height, std::size_t width, const std::string& seed)
{
	bool createPassages = true;
	maze = Maze(height, width, createPassages);

	nextGroupId = 0;
	getPassagesInRandomOrder(seed);
}

auto RandomizedKruskals::getMaze() const -> const Maze&
{
	return maze;
}

auto RandomizedKruskals::step() -> bool
{
	if (activePassage.has_value())
	{
		auto v1 =
			maze.cellValue(activePassage->first.row, activePassage->first.column);

		auto v2 = maze.cellValue(
			activePassage->second.row, activePassage->second.column);

		if (v1.groupId == 0 && v2.groupId == 0)
		{
			++nextGroupId;
			auto groupId = nextGroupId;

			if (activePassage->first.column == activePassage->second.column)
			{
				maze.setSouthPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}
			else
			{
				maze.setEastPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}

			maze.setCell(
				activePassage->first.row,
				activePassage->first.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});

			maze.setCell(
				activePassage->second.row,
				activePassage->second.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});
		}
		else if (v1.groupId > 0u && v2.groupId == 0)
		{
			auto groupId = v1.groupId;

			if (activePassage->first.column == activePassage->second.column)
			{
				maze.setSouthPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}
			else
			{
				maze.setEastPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}

			maze.setCell(
				activePassage->first.row,
				activePassage->first.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});

			maze.setCell(
				activePassage->second.row,
				activePassage->second.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});
		}
		else if (v1.groupId == 0u && v2.groupId > 0)
		{
			auto groupId = v2.groupId;

			if (activePassage->first.column == activePassage->second.column)
			{
				maze.setSouthPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}
			else
			{
				maze.setEastPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}

			maze.setCell(
				activePassage->first.row,
				activePassage->first.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});

			maze.setCell(
				activePassage->second.row,
				activePassage->second.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});
		}
		else if (v1.groupId > 0u && v2.groupId > 0 && v1.groupId == v2.groupId)
		{
			auto groupId = v2.groupId;

			if (activePassage->first.column == activePassage->second.column)
			{
				maze.setSouthPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::Wall, 0});
			}
			else
			{
				maze.setEastPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::Wall, 0});
			}

			maze.setCell(
				activePassage->first.row,
				activePassage->first.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});

			maze.setCell(
				activePassage->second.row,
				activePassage->second.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});
		}
		else if (v1.groupId > 0u && v2.groupId > 0 && v1.groupId != v2.groupId)
		{
			auto groupId = std::min(v1.groupId, v2.groupId);
			auto groupToMerge = std::max(v1.groupId, v2.groupId);

			if (activePassage->first.column == activePassage->second.column)
			{
				maze.setSouthPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}
			else
			{
				maze.setEastPassage(
					std::min(activePassage->first.row, activePassage->second.row),
					std::min(activePassage->first.column, activePassage->second.column),
					{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
					 groupId});
			}

			maze.setCell(
				activePassage->first.row,
				activePassage->first.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});

			maze.setCell(
				activePassage->second.row,
				activePassage->second.column,
				{Core::Mazes::RandomizedKruskals::CellStatus::Visited, groupId});

			for (auto i = 0u; i < maze.height(); i++)
			{
				for (auto j = 0u; j < maze.width(); j++)
				{
					if (maze.cellValue(i, j).groupId == groupToMerge)
					{
						maze.setCell(
							i,
							j,
							{Core::Mazes::RandomizedKruskals::CellStatus::Visited,
							 groupId});
					}

					if (j < maze.width() - 1
						&& maze.eastPassageValue(i, j).groupId == groupToMerge)
					{
						maze.setEastPassage(
							i,
							j,
							{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
							 groupId});
					}
					if (i < maze.height() - 1
						&& maze.southPassageValue(i, j).groupId == groupToMerge)
					{
						maze.setSouthPassage(
							i,
							j,
							{Core::Mazes::RandomizedKruskals::PassageStatus::InGroup,
							 groupId});
					}
				}
			}
		}

		activePassage = std::nullopt;
		return passagesIt != passages.end();
	}
	else
	{
		activePassage = *passagesIt;
		passagesIt++;

		maze.setCell(
			activePassage->first.row,
			activePassage->first.column,
			{Core::Mazes::RandomizedKruskals::CellStatus::Active,
			 maze.cellValue(activePassage->first.row, activePassage->first.column)
				 .groupId});

		maze.setCell(
			activePassage->second.row,
			activePassage->second.column,
			{Core::Mazes::RandomizedKruskals::CellStatus::Active,
			 maze.cellValue(activePassage->second.row, activePassage->second.column)
				 .groupId});

		return true;
	}
}

void RandomizedKruskals::getPassagesInRandomOrder(const std::string& seed)
{
	passages.clear();

	passages.reserve(
		((maze.height() - 1) * maze.width())
		+ (maze.height() * (maze.width() - 1)));

	for (auto i = 0u; i < maze.width(); i++)
	{
		for (auto j = 0u; j < maze.height(); j++)
		{
			if (i < maze.width() - 1)
				passages.emplace_back(Coordinates{i, j}, Coordinates{i + 1, j});
			if (j < maze.height() - 1)
				passages.emplace_back(Coordinates{i, j}, Coordinates{i, j + 1});
		}
	}
	std::default_random_engine engine(std::hash<std::string_view>{}(seed));
	std::shuffle(passages.begin(), passages.end(), engine);

	passagesIt = passages.begin();
}

} // namespace Core::Mazes
