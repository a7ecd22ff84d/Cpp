add_test(NAME TestPyTools
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../
        COMMAND python3 -m unittest TestsPyTools/tests_DbGenerator.py)