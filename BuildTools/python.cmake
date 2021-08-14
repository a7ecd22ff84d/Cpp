set(Venv_path ${CMAKE_SOURCE_DIR}/.venv)
set(Requirements_file ${CMAKE_SOURCE_DIR}/requirements.txt)
set(Cache_help "Used to track changes in requirements.txt file. Allows to install python packages only when necessary")
set(Requirements_cached_timestamp 0 CACHE STRING ${Cache_help})

find_package (Python3 REQUIRED COMPONENTS Interpreter)

if (NOT EXISTS ${Venv_path}/bin/activate)
    execute_process(COMMAND ${Python3_EXECUTABLE} -m venv ${Venv_path})
    message(FATAL_ERROR 
        "Python virtual environment not found, created new one in ${Venv_path}\n"
        "Please activate it and rerun CMake")
elseif("$ENV{VIRTUAL_ENV}" STREQUAL "")
    message(FATAL_ERROR
        "Python virtual environment found in ${Venv_path}\n"
        "Please activate it and rerun CMake")
endif()

file(TIMESTAMP ${Requirements_file} Requirements_timestamp)

if (${Requirements_cached_timestamp} STRLESS ${Requirements_timestamp})
    execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install -r ${Requirements_file})
    set(Requirements_cached_timestamp ${Requirements_timestamp} CACHE STRING ${Cache_help} FORCE)
endif()
