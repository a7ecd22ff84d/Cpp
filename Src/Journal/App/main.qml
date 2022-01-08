import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    id: window
    visible: true
    width: 640
    height: 320
    title: qsTr("MyApp")
    minimumWidth: 640;
    minimumHeight: 320;

    property int buttonsPanelWidth: 200

    Rectangle{
        id: recentFilesRect
        height: parent.height
        width: parent.width - buttonsPanelWidth

        Rectangle{
            id: recentFilesRectMargin
            anchors.fill: parent
            anchors.margins: 10

             Text {
                 id: recentFiles
                 text: "Recent files:"
                 font.bold: true
                 anchors.left: parent.left
                 anchors.leftMargin: 10
                 anchors.top: parent.top
                 anchors.topMargin: 5
             }

             Button
             {
                 id: recentButton
                 text: "Database1"
                 height: 30
                 width: parent.width
                 anchors.top: recentFiles.bottom

                 contentItem: Label {
                         text: parent.text
                         font: parent.font
                         verticalAlignment: Text.AlignVCenter
                         horizontalAlignment: Text.AlignLeft
                 }
             }

             Button
             {
                 id: recentButton2
                 text: "Database2"
                 height: 30
                 width: parent.width
                 anchors.top: recentButton.bottom
                 anchors.topMargin: 5

                 contentItem: Label {
                         text: parent.text
                         font: parent.font
                         verticalAlignment: Text.AlignVCenter
                         horizontalAlignment: Text.AlignLeft
                 }
             }

             Button
             {
                 id: recentButton3
                 text: "Database3"
                 height: 30
                 width: parent.width
                 anchors.top: recentButton2.bottom

                 contentItem: Label {
                         text: parent.text
                         font: parent.font
                         verticalAlignment: Text.AlignVCenter
                         horizontalAlignment: Text.AlignLeft
                 }
             }
        }
    }

    Rectangle{
        id: buttonsRect
        height: parent.height
        width: buttonsPanelWidth
        anchors.left: recentFilesRect.right

        Rectangle{
            id: buttonsRectMargin
            anchors.fill: parent
            anchors.margins: 10

            Text {
                id: motivationalQuote
                text: "\"Threre should be\n   some motivational quote :)\""
                font.bold: true
                anchors.top: parent.top
                anchors.topMargin: 50
            }

            Button
            {
                id: createButton
                text: "Create"
                height: 30
                width: parent.width
                anchors.top: motivationalQuote.bottom
                anchors.topMargin: 50
            }

            Button
            {
                id: addButton
                text: "Add"
                height: 30
                width: parent.width
                anchors.top: createButton.bottom
                anchors.topMargin: 5
            }

            Button
            {
                id: deleteButton
                text: "Delete"
                height: 30
                width: parent.width
                anchors.top: addButton.bottom
                anchors.topMargin: 5
            }
        }
    }
}
