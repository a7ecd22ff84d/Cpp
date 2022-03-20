import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

Rectangle{
    color: 'gray'

    signal activeTabChange(string activeTab)

    Column{
        id: buttons
        property string activeTab: "currentDay"

        spacing: 2
        anchors{
            fill: parent
            margins: 2
        }

        SidebarButton{
            id: currentDayButton
            buttonId: "currentDay"
            icon.source: "qrc:/Icons/Icons/calendar.svg"
        }

        SidebarButton{
            id: journalButton
            buttonId: "journal"
            icon.source: "qrc:/Icons/Icons/notebook.svg"
        }

        SidebarButton{
            id: tasksButton
            buttonId: "tasks"
            icon.source: "qrc:/Icons/Icons/checkup-list.svg"
        }

        SidebarButton{
            id: habitsButton
            buttonId: "habits"
            icon.source: "qrc:/Icons/Icons/chart-bar.svg"
        }

        SidebarButton{
            id: settingsButton
            buttonId: "settings"
            icon.source: "qrc:/Icons/Icons/settings.svg"
        }
    }
}
