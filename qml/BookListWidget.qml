import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import LibSorter 1.0

Widget {
    id: bookList
    title: "Книги"

    property LibCoreBridge bridge: null

    Component.onCompleted: refresh()

    function refresh() {
        if (bridge) {
            booksModel.bookData = bridge.bookList()
        }
    }

    ListView {
        id: booksModel
        anchors.fill: parent
        clip: true
        spacing: 4

        property var bookData: []
        model: bookData

        delegate: Rectangle {
            width: booksModel.width
            height: 50
            color: "#45475a"
            radius: 4

            RowLayout {
                anchors.fill: parent
                anchors.margins: 8

                Text {
                    Layout.fillWidth: true
                    text: "[" + modelData.id + "] " + modelData.title + " — " + modelData.author
                    color: "#cdd6f4"
                    elide: Text.ElideRight
                }

                Text {
                    text: "(" + modelData.available + " доступно)"
                    color: "#a6adc8"
                }
            }
        }
    }
}
