import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import "./Components" as Components
import "./Pages" as Pages

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

        onActiveTabChange: {
            console.log("onActiveTabChange")
            workArea.clear()
            switch(activeTab){
            case "currentDay":
                workArea.push(currentDayPage);
                break
            case "journal":
                workArea.push(journalPage);
                break
            }
        }
    }

    StackView{
        id: workArea

        width: parent.width -sidebar.width
        height: parent.height
        anchors{
            left: sidebar.right
            top: parent.top
        }

        initialItem: currentDayPage
    }

    Component{
        id: currentDayPage
        Pages.CurrentDay{ }
    }

    Component{
        id: journalPage
        Pages.Journal{}
    }
}

