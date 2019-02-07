import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: pageProductsRect
    width: 100
    height: 62

    function changePurchase(purchase) {
        productsList.model = HumbleApi.productsModel(purchase);
    }

    function platformIcon(platform) {
        console.log(platform);
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
        id: productsListDelegate
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
                        console.log(intname);
                    }
                }
            }
            Image {
                id:icon
                anchors.verticalCenter: backgroundRect.verticalCenter
                anchors.left: backgroundRect.left
                anchors.margins: 10
                width: this.height
                height: parent.height - 10
                source: iconurl
            }

            Text {
                id: txt
                anchors.verticalCenter: backgroundRect.verticalCenter
                anchors.left: icon.right
                anchors.margins: 10
                text: humanname
                color: "black"
            }

            GridView {
                id: platforms
                flow: GridView.FlowTopToBottom
                layoutDirection: Qt.RightToLeft
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.margins: 10
                anchors.left: txt.right
                cellHeight: icon.width/2.5
                cellWidth: icon.width/2.5
                model: HumbleApi.productPlatforms(id)

                delegate: Image {
                    anchors.margins: 10
                    sourceSize.width: icon.width/3
                    sourceSize.height: icon.height/3
                    source: platformIcon(platform)
                }
            }
        }
    }

    // visible stuff

    ListView {
        id: productsList
        anchors.fill: parent
        delegate: productsListDelegate
        cacheBuffer: 100
        clip: true
        Label {
            id:noData
            anchors.fill: parent
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment:  Qt.AlignVCenter
            text: qsTr("No downloadable products.")
            visible: parent.count < 1
        }
        ScrollBar.vertical: ScrollBar {}
    }
}
