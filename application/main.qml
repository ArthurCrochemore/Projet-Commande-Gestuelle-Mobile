import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    width: 320
    height: 480
    visible: true
    title: qsTr("Interface Simple")

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"

        Button {
            text: qsTr("Volume")
        }
    }
}
