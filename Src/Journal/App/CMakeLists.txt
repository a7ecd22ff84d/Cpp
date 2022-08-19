add_executable(JournalApp
    main.cpp
    LoginDialog.qml
    LoginButton.qml
    qml.qrc
    Controllers/JournalPageController.cpp
    Controllers/LoginDialogController.cpp
    Gui/Dialog/DummyDialog.qml
    Models/JournalEntriesModel.cpp
)

set_target_properties(JournalApp PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_link_libraries(JournalApp PRIVATE
    Qt5::Core
    Qt5::Quick
    date
    yaml-cpp
    Database
    JrnlDatabase
)

target_compile_definitions(JournalApp PRIVATE 
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
