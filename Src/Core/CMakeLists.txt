add_library(Core
	Date/DateSqlParam.cpp
	Mazes/RandomizedKruskals.cpp
	Mazes/RecursiveBacktrackingGenerator.cpp
	Random/RandomTextGenerator.cpp
	Random/VariableRangeRng.cpp
	SfmlTools/ScreenCapturer.cpp
	Time/FpsCounter.cpp
)

target_link_libraries(Core
	date
	fmt
	sfml-graphics
	Database
	SQLite
)