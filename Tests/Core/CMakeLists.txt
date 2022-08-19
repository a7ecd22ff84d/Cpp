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
	date
	Core
	Database
)

add_test(NAME CoreTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND CoreTests)