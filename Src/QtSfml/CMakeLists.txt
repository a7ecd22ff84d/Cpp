add_library(QtSfml
    QtSfmlCanvas.cpp
)

set_target_properties(QtSfml PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_link_libraries(QtSfml PRIVATE
    fmt
    Qt5::Widgets
    sfml-graphics
)