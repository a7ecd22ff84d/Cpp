import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import "./Components" as Components

Window {
    id: mainWindow
    width:480
    height:320

    Components.Sidebar{
        id: sidebar
        width: 50
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
    }
}
