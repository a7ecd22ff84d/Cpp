add_executable(SqlGenTests
	main.cpp
    GeneratorTests.cpp
)

target_link_libraries(SqlGenTests 
	gmock
	gtest
	pthread
	SqlGen
	yaml-cpp
)

target_include_directories(SqlGenTests PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME SqlGenTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND SqlGenTests)