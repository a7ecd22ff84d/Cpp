add_library(SQLite sqlite3.c)

target_link_libraries(SQLite PRIVATE pthread dl)

target_include_directories(SQLite INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# header file is copied into amalgation .c file, no need to add include
# directories for this library  
# target_include_directories(SQLite PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/sqlite)