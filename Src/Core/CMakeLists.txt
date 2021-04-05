add_library(Core
	Mazes/BaseGenerator.cpp
	Mazes/GeneratorFactory.cpp
	Mazes/RandomizedKruskals.cpp
	Mazes/RecursiveBacktrackingGenerator.cpp
	Random/VariableRangeRng.cpp
)

target_link_libraries(Core
)