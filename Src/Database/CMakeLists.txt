add_library(Database
	Dataset.cpp
	Database.cpp
	Query.cpp
	ParamSetter.cpp
	ValueGetter.cpp
)

target_link_libraries(Database
	fmt
	SQLite
)