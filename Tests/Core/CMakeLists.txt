add_executable(CoreTests
	main.cpp
	Containers/ContainsTests.cpp
	Containers/LoopIteratorTests.cpp
	Date/DateSqlParamTests.cpp
	Factory/RegistrableFactoryTests.cpp
	Random/VariableRangeRngTests.cpp
	Types/DemangledTypeNameTests.cpp
    Types/IsOptionalTests.cpp
)

target_link_libraries(CoreTests
	gmock
	gtest
	pthread
	Core
	date
	Database
)

target_include_directories(CoreTests PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME CoreTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND CoreTests)