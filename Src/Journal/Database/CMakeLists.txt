add_library(JrnlDatabase
    Database.cpp
)

target_link_libraries(JrnlDatabase PRIVATE
    Database
    SqlGen
	SQLite
    yaml-cpp # not needed
)