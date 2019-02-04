import QtQuick 2.0

Rectangle {
    id: pageBundlesRect
    width: 100
    height: 62

    readonly property string __orderListUrl: "https://hr-humblebundle.appspot.com/api/v1/user/order";
    property bool loading: false

    function reloadBundles() {
        pageBundlesRect.loading = true;
        var data = "ajax=true";

        var xhr = new XMLHttpRequest();
        xhr.open("GET", __orderListUrl, true);

        xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        xhr.setRequestHeader("Content-length", data.length);
        xhr.setRequestHeader("X-Requested-By","hb_android_app");

        xhr.onreadystatechange = function() {
            if (xhr.readyState == xhr.DONE) {
                if (xhr.status == 200) {
                    parseBundles(JSON.parse(xhr.responseText));
                } else if (xhr.status == 0) {
                    console.log("Error: ", xhr.status, xhr.statusText);
                    // this typically happens if no internet connection is there at all
                }
            }  else if (xhr.status == 401) {
                console.log("need to relogin");
                pageLogin.visible = true;
            } else if (xhr.status != 200) {
                console.log("Error: ", xhr.status)
            }
            pageBundlesRect.loading = false;
        }
        xhr.send(data);
    }

    function parseBundles(json) {
        var sortArray = []
        for(var i = 0; i < json.length; ++i) {
            var element = json[i];
            if (element["product"]["category"] == "bundle") {
                sortArray.push({
                                   "human_name"   : element["product"]["human_name"],
                                   "machine_name" : element["product"]["machine_name"]
                               })
            }
        }

        sortArray.sort(function (lhs, rhs) {
            return lhs["human_name"] <= rhs["human_name"] ? -1 :1;
        });

        for (var i = 0; i < sortArray.length; ++i) {
            bundlesListModel.append(sortArray[i]);
        }
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
