add_library(JrnlDatabase
    Database.cpp
)

set(TableDefinitions
    ${CMAKE_CURRENT_SOURCE_DIR}/Tables/Entry.yaml)

add_custom_target(CopyTableDefinitions
    cmake -E copy ${TableDefinitions} ${CMAKE_BINARY_DIR}/Tables
    COMMENT "Copying journal table definitions"
    DEPENDS ${TableDefinitions}
    SOURCES ${TableDefinitions}
)

# add_dependencies(CopyTableDefinitions JrnlDatabase)

target_link_libraries(JrnlDatabase PRIVATE
    Database
    SqlGen
	SQLite
    yaml-cpp # not needed
)