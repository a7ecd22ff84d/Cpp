add_executable(DatabaseTests
	main.cpp
	DatabaseTests.cpp
	DatasetTests.cpp
	QueryTests.cpp
	TypesTests.cpp
	Tools/TestTable.cpp
)

target_link_libraries(DatabaseTests 
	gmock
	gtest
	pthread
    Database
)

target_include_directories(DatabaseTests PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME DatabaseTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND DatabaseTests)