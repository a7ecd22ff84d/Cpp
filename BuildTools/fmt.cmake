set(fmt_version 7.1.3)
set(fmt_directory "${CMAKE_SOURCE_DIR}/Libraries/fmt-${fmt_version}")

if (NOT EXISTS ${fmt_directory})
    execute_process (
        COMMAND git clone --depth 1 -c advice.detachedHead=false --branch ${fmt_version}
        "https://github.com/fmtlib/fmt.git"
        ${fmt_directory})
endif()
