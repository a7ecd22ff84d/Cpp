add_executable(QtSfmlDemo
    ../../Res/Resources.qrc
    BaseDemo.cpp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    AboutDialog.ui
    AboutDialog.cpp
    AboutDialog.h
    Algorithms/Gradient/GradientControls.ui
    Algorithms/Gradient/GradientProgram.cpp
    Algorithms/Gradient/GradientProgram.h
    Algorithms/MazeGenerator/MazeControls.ui
    Algorithms/MazeGenerator/MazePrinter.cpp
    Algorithms/MazeGenerator/MazePrinter.h
    Algorithms/MazeGenerator/MazeProgram.cpp
    Algorithms/MazeGenerator/MazeProgram.h
    Common/GridPrinter.cpp
    Demos/GridPrinter/GridPrinterDemo.cpp
    Demos/Init/InitProgram.cpp
    Demos/QtSfmlDemo/QtSfmlDemo.h
    Demos/QtSfmlDemo/QtSfmlDemo.cpp
    Demos/QtSfmlDemo/QtSfmlDemo.ui
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
    Core
)

set_target_properties(QtSfmlDemo PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
