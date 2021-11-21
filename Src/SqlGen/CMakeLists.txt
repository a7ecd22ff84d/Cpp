add_library(SqlGen
    Generator.cpp
)

target_link_libraries(SqlGen PRIVATE
    nlohmann_json
)