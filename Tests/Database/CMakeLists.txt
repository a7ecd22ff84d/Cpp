add_executable(DatabaseTests
    main.cpp
    QueryTests.cpp
)

target_link_libraries(DatabaseTests 
	gmock
	gtest
	pthread
    Database
)

add_test(NAME DatabaseTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND DatabaseTests)