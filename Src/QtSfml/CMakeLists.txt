add_library(QtSfml
    QtSfmlCanvas.cpp
)

target_link_libraries(QtSfml PRIVATE
    fmt
    Qt5::Widgets
    sfml-graphics
)