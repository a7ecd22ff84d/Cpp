set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt5_add_resources(QT_RESOURCES qml.qrc)


add_executable(QmlSfml
    main.cpp
    SfmlWindow.cpp
    ${QT_RESOURCES}
)

target_link_libraries(QmlSfml
    Qt5::Widgets
    Qt5::Qml
    Qt5::Quick
    sfml-graphics
)

target_include_directories(QmlSfml PRIVATE
    ${Qt5Widgets_INCLUDE_DIRS}
    ${QtQml_INCLUDE_DIRS}
    ${SFML_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Src
)

target_compile_definitions(QmlSfml PRIVATE
    ${Qt5Widgets_DEFINITIONS}
    ${QtQml_DEFINITIONS}
    ${${Qt5Quick_DEFINITIONS}}
)