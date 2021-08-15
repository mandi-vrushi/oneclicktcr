import QtQuick
Row {
    anchors {
        left: parent.left
        right: parent.right
    }
    implicitHeight: textRow.height
    Text {
        id: textRow
        text: qsTr("text")
    }
}
