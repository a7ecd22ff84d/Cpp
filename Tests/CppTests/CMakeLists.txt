add_executable(CppTests
	main.cpp
	IsStringNumberTests.cpp
	LifetimeTests.cpp
	SharedPtrTests.cpp
)

target_link_libraries(CppTests 
	gmock
	gtest
	pthread
)

add_test(NAME CppTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND CppTests)