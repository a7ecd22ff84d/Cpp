# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

# find_package(Qt5 COMPONENTS Core Quick REQUIRED)


add_executable(JournalApp
    main.cpp
    DatabaseManager.cpp
    LoginDialog.qml
    LoginButton.qml
    qml.qrc
    Gui/Dialog/DummyDialog.qml
    Models/JournalEntriesModel.cpp
)

target_link_libraries(JournalApp PRIVATE
    date
    JrnlDatabase
)

target_compile_definitions(JournalApp
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(JournalApp
  PRIVATE Qt5::Core Qt5::Quick)


# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# # Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# # They need to be set before the find_package(Qt5 ...) call.

# #if(ANDROID)
# #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
# #    if (ANDROID_ABI STREQUAL "armeabi-v7a")
# #        set(ANDROID_EXTRA_LIBS
# #            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
# #            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
# #    endif()
# #endif()

# find_package(Qt5 COMPONENTS Core Quick REQUIRED)

# if(ANDROID)
#     add_library(JornalApp SHARED
#       main.cpp
#       qml.qrc
#     )
# else()
#     add_executable(JornalApp
#       main.cpp
#       qml.qrc
#     )
# endif()

# target_compile_definitions(JornalApp
#   PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
# target_link_libraries(JornalApp
#   PRIVATE Qt5::Core Qt5::Quick)

