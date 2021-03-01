add_executable(QtSfml
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    QtSfmlCanvas.cpp
)

target_link_libraries(QtSfml PRIVATE Qt5::Widgets sfml-graphics)
