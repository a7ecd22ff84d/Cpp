add_test(NAME TestPyTools
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/
        COMMAND python -m unittest discover -s TestsPyTools/ -p *tests_*.py)