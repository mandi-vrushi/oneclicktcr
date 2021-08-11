import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.VirtualKeyboard

ApplicationWindow {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("One Click TCR")



    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&New...")
                icon.source: "qrc:/icons/light/file.svg"
                icon.color: "yellow"
                icon.width: 0.75 * icon.height
            }
            Action { text: qsTr("&Open...") }
            Action { text: qsTr("&Save") }
            Action { text: qsTr("Save &As...") }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
        Menu {
            title: qsTr("&Edit")
            Action {
                text: qsTr("Cu&t")
                icon.name: "edit-cut"
            }
            Action { text: qsTr("&Copy") }
            Action { text: qsTr("&Paste") }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About") }
        }
    }
    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                icon.source: "qrc:/icons/light/angle-left.svg"
                icon.color: "white"
            }
            Label {
                text: "Title"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                icon.source: "qrc:/icons/light/ellipsis-v.svg"
                onClicked: menu.open()
            }
        }
    }


    Button {

        id: buttonId
        width: 100
        height: 50
        text: "Click"
        icon.source: "qrc:/icons/light/comment-dots.svg"
        palette.buttonText: "red"
        spacing: 5
        anchors.centerIn: parent
        onClicked: {
            inputPanel.active = !inputPanel.active
        }
    }

    Button {
        id: buttonId2
        width: 100
        height: 50
        enabled: false
        text: "Click"
        icon.source: "qrc:/icons/light/comment-dots.svg"
        contentItem: Item {
            anchors.fill: parent
            Row{
                anchors.centerIn: parent
                spacing: 5
                Image {
                    source: buttonId2.icon.source
                    width: buttonId2.icon.width
                    height: buttonId2.icon.height
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    text: buttonId2.text
                    font: buttonId2.font
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        anchors.top : buttonId.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            inputPanel.active = !inputPanel.active
        }
    }

    TextInput {
        Text {
            text: "Test prova 123"
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: mainWindow.height
        width: mainWindow.width
        MultiPointTouchArea {
            touchPoints: [
                TouchPoint { id: point1}
            ]
        }

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: mainWindow.height - inputPanel.height - footer.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
    footer: TabBar {

    }

}
