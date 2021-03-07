add_library(QtSfml
    QtSfmlCanvas.cpp
)

target_link_libraries(QtSfml PRIVATE
    Qt5::Widgets
    sfml-graphics
)