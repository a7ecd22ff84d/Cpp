# Target created to test if source file generation scripts works correctly 
# with CMake. Existence and compilability of generated files is checked by
# target GenerateEntityTestLib. Content of this files should be checked manually.
# Generated files are stored in OUTPUT_DIR path

set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Output)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

add_custom_command(
    COMMENT "Entity generation tests"
    OUTPUT ${OUTPUT_DIR}/TestTable.cpp
    OUTPUT ${OUTPUT_DIR}/TestTable.h 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/SampleDefinition.yaml
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND export PYTHONPATH=${CMAKE_SOURCE_DIR} && python PyTools/generateEntity.py ${CMAKE_CURRENT_SOURCE_DIR}/SampleDefinition.yaml ${OUTPUT_DIR} --namespace Entity
)

# CMake won't run previous command without generated files being used
add_library(GenerateEntityTestLib
    ${OUTPUT_DIR}/TestTable.cpp
)

target_include_directories(GenerateEntityTestLib PRIVATE ${OUTPUT_DIR})