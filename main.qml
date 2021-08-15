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
//            inputPanel.active = !inputPanel.active
            trayIcon.print("mainWindow.gra")
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
    onClosing: {
        trayIcon.unloadWindow(this);
    }

}
