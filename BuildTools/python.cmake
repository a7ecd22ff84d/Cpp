# find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(VIRTUAL_ENV_PATH "${CMAKE_SOURCE_DIR}/.venv")
set(VENV_TIMESTAMP_FILE "${CMAKE_SOURCE_DIR}/build/.venv_timestamp")

# if ()

# execute_process (COMMAND "${Python3_EXECUTABLE}" -m venv "${VIRTUAL_ENV_PATH}")

# set (ENV{VIRTUAL_ENV} "${VIRTUAL_ENV_PATH}")
# set (Python3_FIND_VIRTUALENV FIRST)

# unset (Python3_EXECUTABLE)
# find_package (Python3 REQUIRED COMPONENTS Interpreter Development)

# execute_process (COMMAND "${Python3_EXECUTABLE}" -m venv "${VIRTUAL_ENV_PATH}")

# set up virtual env
