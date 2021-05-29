add_library(Core
	Mazes/BaseGenerator.cpp
	Mazes/GeneratorFactory.cpp
	Mazes/RandomizedKruskals.cpp
	Mazes/RecursiveBacktrackingGenerator.cpp
	SfmlTools/ScreenCapturer.cpp
	Time/FpsCounter.cpp
	Random/VariableRangeRng.cpp
)

target_link_libraries(Core
	sfml-graphics
)