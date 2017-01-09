
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    width: 540
    height: 960
    visible: true


    Page {
        anchors.fill: parent

        ComboBox {
            id:comboBox
            Layout.alignment: Qt.AlignCenter
            width: parent.width
            height:50
            model: comboModel

            onCurrentIndexChanged: {
                console.debug(comboModel[currentIndex])
                cpuModel.updateModel(currentIndex)
                //listView.update()
                listView.currentIndex = 0

            }
            z: 2
        }

        ListView {
            id: listView
            z: 1
            Layout.alignment: Qt.AlignCenter
            width: parent.width
            height: parent.height - comboBox.height
            x:  0
            y:  comboBox.height + 20
            bottomMargin: 20
            spacing: 5
            focus: true
            highlightMoveDuration:20
            highlight:  Item {
                Rectangle{
                    color: "gray"
                    radius: 3
                    width:  parent.width - 10
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            model: cpuModel
            delegate: ItemDelegate {
                text: Info

                width:  listView.width - listView.leftMargin - listView.rightMargin
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index
                    }
                }
            }
        }
    }
}
