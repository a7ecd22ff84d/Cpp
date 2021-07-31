add_custom_command(
    COMMENT "Entity generation tests"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../Output/TestTable.cpp
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../Output/TestTable.h 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/SampleDefinition.yaml
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND export PYTHONPATH=${CMAKE_SOURCE_DIR} && ${CMAKE_SOURCE_DIR}/.venv/bin/python PyTools/generateEntity.py ${CMAKE_CURRENT_SOURCE_DIR}/SampleDefinition.yaml ${CMAKE_CURRENT_SOURCE_DIR}/../Output --namespace Entity
)

add_library(TestLib
    ${CMAKE_CURRENT_SOURCE_DIR}/../Output/TestTable.cpp
)

target_include_directories(TestLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Output)