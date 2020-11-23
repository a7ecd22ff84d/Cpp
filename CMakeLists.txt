cmake_minimum_required(VERSION 3.19)
project(CppMess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS YES)

include (BuildTools/sqlite.cmake)

add_subdirectory(Libraries/sqlite-3.33.0)

add_custom_target(Doc ALL 
    make html
    WORKING_DIRECTORY ../Docs)
