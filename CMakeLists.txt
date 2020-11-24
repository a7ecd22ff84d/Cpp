cmake_minimum_required(VERSION 3.19)
project(CppMess)

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

include (BuildTools/sqlite.cmake)
include (BuildTools/googletest.cmake)

set(INSTALL_GTEST ON CACHE BOOL false)

add_subdirectory(Libraries/sqlite-3.33.0)
add_subdirectory(Libraries/googletest-1.10.0)

add_custom_target(Doc ALL 
    make html
    WORKING_DIRECTORY ../Docs)
