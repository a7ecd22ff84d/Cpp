import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

Button{
    property string buttonId

    id: currentDayButton

    width: parent.width
    height: parent.width
    highlighted: parent.activeTab === buttonId

    onClicked: {
        parent.activeTab = buttonId
    }
}
