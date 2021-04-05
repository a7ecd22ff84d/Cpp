add_library(Core
	Generator/Maze/RandomizedKruskals.cpp
	Generator/Maze/RecursiveBacktrackingGenerator.cpp
	Random/VariableRangeRng.cpp
)

target_link_libraries(Core
)