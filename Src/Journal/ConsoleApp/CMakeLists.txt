add_executable(jrnlc
    main.cpp
)

target_link_libraries(jrnlc PRIVATE
    JrnlDatabase
    Database
    SqlGen
	SQLite
    yaml-cpp # not needed
)