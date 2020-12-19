set(googletest_version 1.10.0)
set(googletest_directory "${CMAKE_SOURCE_DIR}/Libraries/googletest-${googletest_version}")

if (NOT EXISTS ${googletest_directory})
    execute_process (
        COMMAND git clone --depth 1 -c advice.detachedHead=false --branch release-${googletest_version}
        "https://github.com/google/googletest.git"
        ${googletest_directory})
endif()
