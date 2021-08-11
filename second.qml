import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.VirtualKeyboard

Window {
    id: secodWindow
    width: 640
    height: 480
    title: qsTr("Second Window")

    TextInput {
        id: text1
    }
}
