import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12

import Journal 1.0

Item {
    anchors.fill: parent
    property int rightColumnWidth: 280

    JournalPageController
    {
        id: pageController
    }

    Rectangle{
        id: editorArea
        color: "lightblue"

        height: parent.height
        width: parent.width - rightColumnWidth
        anchors
        {
            top: parent.top
            left: parent.left
        }

        TextArea {
            id: textArea
            anchors.fill: parent
            enabled: false
        }
    }

    Rectangle{

        width: rightColumnWidth
        height: parent.height

        anchors
        {
            top: parent.top
            left: editorArea.right
        }

        Calendar{
            id: dateSelectionCalendar
            height: 220
            transformOrigin: Item.Center
            weekNumbersVisible: true
            width: parent.width
            anchors{
                bottom: parent.bottom
                left: parent.left
            }
        }

        Rectangle{
            id: entryBrowserArea

            EntriesModel
            {
                id: entriesModel
            }

            ListView {
                width: 100
                height: 100

                model: pageController.entriesModel
                anchors.fill: parent

                interactive: false
                spacing: 1

                delegate: Rectangle {
                    color: Qt.rgba(0.9,0.9,0.9)
                    height: 20
                    width: parent.width

                    Text {
                        text: model.date + " - " + model.title
                        anchors
                        {
                            left:parent.left;
                            verticalCenter: parent.verticalCenter;
                            leftMargin: 5
                        }
                    }
                }
            }

            width: parent.width
            height: parent.height - dateSelectionCalendar.height
            anchors{
                top: parent.top
                left: parent.left
            }
            color: "lightgray"
        }
    }
}
