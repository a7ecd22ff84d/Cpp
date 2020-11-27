add_library(Database
	Dataset.cpp
	Database.cpp
	Query.cpp
)

target_link_libraries(Database
	SQLite
)