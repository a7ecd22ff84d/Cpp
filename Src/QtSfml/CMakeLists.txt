add_executable(QtSfml
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    GameEngine.cpp
    QtSfmlCanvas.cpp
)

target_link_libraries(QtSfml PRIVATE
    fmt
    Qt5::Widgets
    sfml-graphics
)