add_library(Database
	Dataset.cpp
	Database.cpp
	Query.cpp
	ParamSetter.cpp
)

target_link_libraries(Database
	SQLite
)