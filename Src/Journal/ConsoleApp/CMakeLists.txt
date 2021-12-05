add_executable(jrnlc
    main.cpp
)

target_link_libraries(jrnlc PRIVATE
    JrnlDatabase
    yaml-cpp # not needed
)