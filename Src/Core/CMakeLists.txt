add_library(Core
	Mazes/BaseGenerator.cpp
	Mazes/RandomizedKruskals.cpp
	Mazes/RecursiveBacktrackingGenerator.cpp
	Random/RandomTextGenerator.cpp
	Random/VariableRangeRng.cpp
	SfmlTools/ScreenCapturer.cpp
	Time/FpsCounter.cpp
)

target_link_libraries(Core
	fmt
	sfml-graphics
)