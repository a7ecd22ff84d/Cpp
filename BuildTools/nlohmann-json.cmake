set(nlohmann-json_version 3.10.4)
set(nlohmann-json_directory "${CMAKE_SOURCE_DIR}/Libraries/nlohmann-json-${nlohmann-json_version}")

if (NOT EXISTS ${nlohmann-json_directory})
    execute_process (
        COMMAND git clone --depth 1 -c advice.detachedHead=false --branch v${nlohmann-json_version}
        "https://github.com/nlohmann/json"
        ${nlohmann-json_directory})
endif()
