execute_process (
    COMMAND git clone --depth 1 --branch release-1.10.0
    "https://github.com/google/googletest.git"
    "${CMAKE_SOURCE_DIR}/Libraries/googletest-1.10.0")
