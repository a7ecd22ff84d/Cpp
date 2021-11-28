cmake_minimum_required(VERSION 3.19)
project(Cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS YES)

add_compile_options(-Wall)
add_compile_options(-pedantic)

link_directories(${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Src)

enable_testing()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# set up python vitualenv
include (BuildTools/python.cmake)

# find external libraries
find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# external libraries download
include (BuildTools/fmt.cmake)
include (BuildTools/googletest.cmake)
include (BuildTools/nlohmann-json.cmake)
include (BuildTools/sqlite.cmake)
include (BuildTools/yaml-cpp.cmake)

# external libraries settings
set(INSTALL_GTEST ON CACHE BOOL false)

#  external libraries
add_subdirectory(Libraries/fmt-7.1.3)
add_subdirectory(Libraries/googletest-1.10.0)
add_subdirectory(Libraries/nlohmann-json-3.10.4)
add_subdirectory(Libraries/sqlite-3.33.0)
add_subdirectory(Libraries/yaml-cpp-0.7.0)

# Src
add_subdirectory(Src/Core)
add_subdirectory(Src/Database)
add_subdirectory(Src/QtSfml)
add_subdirectory(Src/QtSfmlDemo)
add_subdirectory(Src/SqlGen)

# Tests
add_subdirectory(Tests/Core)
add_subdirectory(Tests/CppTests)
add_subdirectory(Tests/Database)
add_subdirectory(Tests/SqlGen)

# python tests
add_subdirectory(PyToolsTests)

## Tests - BuildSystem
## Output have to be checked manually. More info in CMakeLists.txt
add_subdirectory(BuildToolsTests/EntityGeneration)

# Other
add_custom_target(Doc ALL 
    make html
    WORKING_DIRECTORY ../Docs)
