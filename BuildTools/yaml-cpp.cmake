set(yaml_version 0.7.0)
set(yaml_directory "${CMAKE_SOURCE_DIR}/Libraries/yaml-cpp-${yaml_version}")

if (NOT EXISTS ${yaml_directory})
    execute_process (
        COMMAND git clone --depth 1 -c advice.detachedHead=false --branch yaml-cpp-${yaml_version}
        "https://github.com/jbeder/yaml-cpp.git"
        ${yaml_directory})
endif()
