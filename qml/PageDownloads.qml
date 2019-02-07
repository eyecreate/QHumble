import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: pageDownloadsRect
    width: 100
    height: 62

    function changeProduct(product) {
        downloadsList.model = HumbleApi.downloadsModel(product);
    }

    function platformIcon(platform) {
        if(platform === "linux") {
            return "qrc:/qml/assets/images/platform/linux.svg";
        } else if(platform === "mac") {
            return "qrc:/qml/assets/images/platform/mac.svg";
        } else if(platform === "audio") {
            return "qrc:/qml/assets/images/platform/music-solid.svg";
        } else if(platform === "windows") {
            return "qrc:/qml/assets/images/platform/windows.svg";
        } else if(platform === "ebook") {
            return "qrc:/qml/assets/images/platform/book-solid.svg";
        } else if(platform === "android") {
            return "qrc:/qml/assets/images/platform/android.svg";
        } else {
            return "qrc:/qml/assets/images/platform/all.svg";
        }
    }

    Component {
        id: downloadsListDelegate
        Item {
            width: parent.width
            height: 70

            Rectangle {
                id: backgroundRect
                x: 1
                y: 1
                width: parent.width - x*2;
                height: parent.height - y*2
                border.color: "black"
                radius: 5
                opacity: index % 2 ? 0.2 : 0.3
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                    }
                }
            }
            Image {
                id:itemPlatform
                anchors.verticalCenter: backgroundRect.verticalCenter
                anchors.left: backgroundRect.left
                anchors.margins: 10
                sourceSize.width: this.height
                sourceSize.height: parent.height - 10
                source: platformIcon(platform)
            }

            ListView {
                id: files
                orientation: ListView.Horizontal
                layoutDirection: Qt.RightToLeft
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 10
                spacing: 10
                anchors.left: itemPlatform.right
                model: HumbleApi.filesModel(id)

                Label {
                    id:noData
                    anchors.fill: parent
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment:  Qt.AlignVCenter
                    text: qsTr("No downloads.")
                    visible: parent.count < 1
                }

                delegate: Button {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        Qt.openUrlExternally(weburl);
                    }
                }
            }
        }
    }

    // visible stuff

    ListView {
        id: downloadsList
        anchors.fill: parent
        delegate: downloadsListDelegate
        cacheBuffer: 100
        clip: true
        ScrollBar.vertical: ScrollBar {}
    }
}
