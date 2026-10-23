import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import LibSorter 1.0

Item {
    id: canvas

    property string canvasTitle: "canvas"
    property bool editMode: false
    property LibCoreBridge bridge: null

    // Фон
    Rectangle {
        anchors.fill: parent
        color: "#1e1e2e"
    }

    // Кнопка режима редактирования (справа сверху)
    Button {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        text: canvas.editMode ? "Готово" : "Редактировать"
        onClicked: canvas.editMode = !canvas.editMode
    }

    // Холст с виджетами
    Item {
        anchors.fill: parent
        anchors.margins: 10

        BookListWidget {
            x: 0
            y: 0
            width: 600
            height: 400
            bridge: canvas.bridge
            editMode: canvas.editMode
        }
    }
}
