add_executable(QtSfmlDemo
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Algorithms/MazeGenerator/MazeControls.cpp
    Algorithms/MazeGenerator/MazeControls.h
    Algorithms/MazeGenerator/MazeControls.ui
    Algorithms/MazeGenerator/MazeGenerator.cpp
    Algorithms/MazeGenerator/MazeGenerator.h
    Algorithms/MazeGenerator/MazePrinter.cpp
    Algorithms/MazeGenerator/MazePrinter.h
    Algorithms/MazeGenerator/MazeProgram.cpp
    Algorithms/MazeGenerator/MazeProgram.h
    Demos/Init/InitProgram.cpp
    Demos/TestApp/GameControls.cpp
    Demos/TestApp/GameControls.ui
    Demos/TestApp/GameControls.h
    Demos/TestApp/GameEngine.cpp
    Demos/TestApp/TestDemo.cpp
)

target_link_libraries(QtSfmlDemo PRIVATE
    fmt
    sfml-graphics
    Qt5::Widgets
    QtSfml
)