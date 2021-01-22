import QtQuick 2.0
import QtQuick.Controls 1.0
import MyItems 1.0

ApplicationWindow
{
    visible: true
    width: 480
    height: 640
    title: qsTr("Minimal Qml")


    SfmlWindow
    {
        id: aPieChart
        anchors.left: parent.left
        anchors.top: parent.top
        width: 480
        height: 480
        name: "A simple pie chart"
        color: "red"
    }
}