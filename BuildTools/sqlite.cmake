# download sqlite library and put it info Libraries directory

file(DOWNLOAD
    "https://www.sqlite.org/2020/sqlite-amalgamation-3330000.zip"
    "${CMAKE_SOURCE_DIR}/build/sqlite-amalgamation-3330000.zip"
)

file(ARCHIVE_EXTRACT
    INPUT "${CMAKE_SOURCE_DIR}/build/sqlite-amalgamation-3330000.zip"
    DESTINATION "${CMAKE_SOURCE_DIR}/build/")

file(COPY
    "${CMAKE_SOURCE_DIR}/build/sqlite-amalgamation-3330000/sqlite3.c"
    DESTINATION "${CMAKE_SOURCE_DIR}/Libraries/sqlite-3.33.0")

file(COPY
    "${CMAKE_SOURCE_DIR}/build/sqlite-amalgamation-3330000/sqlite3.h"
    DESTINATION "${CMAKE_SOURCE_DIR}/Libraries/sqlite-3.33.0/include/sqlite")
