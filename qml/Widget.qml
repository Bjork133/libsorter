import QtQuick
import QtQuick.Controls

Rectangle {
    id: widget

    property bool editMode: false
    property string title: "Widget"
    default property alias content: contentItem.data

    color: "#313244"
    radius: 8
    border.color: editMode ? "#89b4fa" : "#45475a"
    border.width: editMode ? 2 : 1

    // Заголовок
    Rectangle {
        id: header
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30
        color: "#45475a"
        radius: parent.radius

        Text {
            anchors.centerIn: parent
            text: widget.title
            color: "#cdd6f4"
            font.bold: true
        }

        // Drag handle (только в edit mode)
        MouseArea {
            anchors.fill: parent
            enabled: widget.editMode
            drag.target: widget
            cursorShape: Qt.SizeAllCursor
        }
    }

    // Контент
    Item {
        id: contentItem
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 8
    }
}
