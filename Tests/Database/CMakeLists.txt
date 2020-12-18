add_executable(DatabaseTests
	DatasetTests.cpp
	Tools/TestTable.cpp
	main.cpp
	QueryTests.cpp
	ValueGetterTests.cpp
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