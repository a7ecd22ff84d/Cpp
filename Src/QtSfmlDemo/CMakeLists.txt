add_executable(QtSfmlDemo
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Demos/Init/InitProgram.cpp
    Demos/TestApp/GameEngine.cpp
)

target_link_libraries(QtSfmlDemo PRIVATE
    fmt
    sfml-graphics
    Qt5::Widgets
    QtSfml
)