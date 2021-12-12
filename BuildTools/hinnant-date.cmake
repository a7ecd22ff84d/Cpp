set(date_version 3.0.1)
set(date_directory "${CMAKE_SOURCE_DIR}/Libraries/hinnant-date-${date_version}")

if (NOT EXISTS ${date_directory})
    execute_process (
        COMMAND git clone --depth 1 -c advice.detachedHead=false --branch v${date_version}
        "https://github.com/HowardHinnant/date.git"
        ${date_directory})
endif()
