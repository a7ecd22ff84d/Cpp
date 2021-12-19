# Copying databse definitions to build directory
set(TableDefinitions
    ${CMAKE_CURRENT_SOURCE_DIR}/Tables/Entry.yaml)

add_custom_target(CopyTableDefinitions
    cmake -E copy ${TableDefinitions} ${CMAKE_BINARY_DIR}/Tables
    COMMENT "Copying journal table definitions"
    DEPENDS ${TableDefinitions}
    SOURCES ${TableDefinitions}
)

# Generating database entities before build
set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Entities)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

set(EntityFiles
    ${OUTPUT_DIR}/Entry.cpp
    ${OUTPUT_DIR}/Entry.h 
)

add_custom_command(
    COMMENT "Journal database entities geneation"
    OUTPUT ${EntityFiles}
    DEPENDS ${TableDefinitions}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND export PYTHONPATH=${CMAKE_SOURCE_DIR} && python PyTools/generateEntity.py ${CMAKE_CURRENT_SOURCE_DIR}/Tables/Entry.yaml ${OUTPUT_DIR} ${CMAKE_SOURCE_DIR}/Src --namespace Entities
    COMMAND clang-format -i ${EntityFiles}
)

# Actual library
add_library(JrnlDatabase
    Database.cpp
    Entities/Entry.cpp
)

target_link_libraries(JrnlDatabase PRIVATE
    date
    yaml-cpp # not needed
    Database
    SqlGen
	SQLite
)