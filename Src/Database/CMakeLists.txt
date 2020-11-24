add_library(Database
	Database.cpp
	Query.cpp
)

target_link_libraries(Database
	SQLite
)