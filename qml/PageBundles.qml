import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {
    id: pageBundlesRect
    width: 100
    height: 62

    Connections {
        target: HumbleApi
        onOrderListUpdated: {
            pageBundlesRect.loading = false;
            bundlesList.model = HumbleApi.filterablePurchaseModel();
        }
    }

    Component.onCompleted: {
        if(HumbleApi.isLoggedIn()){
            startUpdate();
        }
    }
    property bool loading: false

    function startUpdate() {
        if(HumbleApi.isRefreshNeeded()) {
            pageBundlesRect.loading = true;
            HumbleApi.updateOrderList();
        } else {
            bundlesList.model = HumbleApi.filterablePurchaseModel();
        }
    }

    function purchaseType(type) {
        if(type === "storefront") {
            return "qrc:/qml/assets/images/purchase/store-solid.svg"
        } else if(type === "widget") {
            return "qrc:/qml/assets/images/purchase/globe-solid.svg"
        } else if(type === "bundle") {
            return "qrc:/qml/assets/images/purchase/sitemap-solid.svg"
        } else if(type === "subscriptionplan" || type === "subscriptioncontent") {
            return "qrc:/qml/assets/images/purchase/wallet-solid.svg"
        } else {
            return "qrc:/qml/assets/images/platform/all.svg"
        }
    }

    function filterList(filter) {
        bundlesList.model.filterKeyColumn = 2;
        bundlesList.model.filterCaseSensitivity = Qt.CaseInsensitive;
        bundlesList.model.setFilterFixedString(filter);
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
                        mainViewManger.currentIndex = 3;
                        pageProducts.changePurchase(id,humbleid);
                    }
                }
            }
            Image {
                id:platformType
                anchors.verticalCenter: backgroundRect.verticalCenter
                anchors.left: backgroundRect.left
                anchors.margins: 10
                width: this.height
                height: parent.height - 10
                source: purchaseType(type)
            }

            Text {
                id: txt
                anchors.verticalCenter: backgroundRect.verticalCenter
                anchors.left: platformType.right
                anchors.margins: 10
                text: humanname
                color: "black"
            }
        }
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
        delegate: bundlesListDelegate
        cacheBuffer: 100
        clip: true

        ScrollBar.vertical: ScrollBar {}
    }

}
