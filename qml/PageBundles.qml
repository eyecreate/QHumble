import QtQuick 2.0

Rectangle {
    id: pageBundlesRect
    width: 100
    height: 62

    Connections {
        target: HumbleApi
        onOrderListUpdated: {
            pagesBundlesRect.loading = false;
        }
    }

    Component.onCompleted: {
        if(HumbleApi.isLoggedIn()){
            startUpdate();
        }
    }
    property bool loading: false

    function startUpdate() {
        pageBundlesRect.loading = true;
        HumbleApi.updateOrderList();
    }

    Component {
        id: bundlesListDelegate
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
                        console.log(machine_name);
                    }
                }
            }
            Text {
                id: txt
                x: backgroundRect.x + 10
                anchors.verticalCenter: backgroundRect.verticalCenter
                text: human_name
                color: "black"
            }
        }
    }

    ListModel {
        id: bundlesListModel
    }

    // visible stuff
    Loading {
        width: 50
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        visible: pageBundlesRect.loading
    }

    ListView {
        id: bundlesList
        anchors.fill: parent
        visible: !pageBundlesRect.loading

        model: bundlesListModel
        delegate: bundlesListDelegate
        cacheBuffer: 100
        clip: true

        Scrollbar {
            flickable: bundlesList
            color: "#FFE4C4"
        }
    }

}
