import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import LibSorter 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    height: 800
    title: "LibSorter"

    LibCoreBridge {
        id: bridge
    }

    Component.onCompleted: {
        // TODO: загрузить профиль из ~/.config/libcore/profiles.json
        // Пока — заглушка
        bridge.setLibrary("Ta")
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Верхняя панель (вкладки + меню)
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 40

            Button {
                text: "+"
                onClicked: tabs.addTab()
            }

            TabBar {
                id: tabBar
                Layout.fillWidth: true

                Repeater {
                    model: tabs.count
                    TabButton {
                        text: tabs.get(tabBar.currentIndex).title
                    }
                }
            }

            Button {
                text: "⚙"
                onClicked: settingsMenu.open()
            }

            Menu {
                id: settingsMenu
                MenuItem { text: "Профили..." }
                MenuItem { text: "Темы..." }
                MenuItem { text: "Настройки..." }
            }
        }

        // Холст
        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex

            Repeater {
                model: tabs
                Canvas {
                    bridge: bridge
                    canvasTitle: model.title
                }
            }
        }
    }

    // Модель вкладок (пока простая)
    ListModel {
        id: tabs
        ListElement { title: "main" }
    }

    function addTab() {
        tabs.append({ title: "canvas_" + tabs.count })
    }
}
