import QtQuick 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Humble Bundle")

    header: ToolBar {
        background: Rectangle {
            implicitHeight:  40
            color: "#cb272c"
            Rectangle {
                height: 1
                width: parent.width
                color: "transparent"
                anchors.bottom: parent.bottom
                border.color: "#494f5c"
            }
        }

        RowLayout {
            anchors.fill: parent
            Image {
                source: "qrc:/qml/assets/images/h_huge.png"
                sourceSize.height: 38
                sourceSize.width: 38
            }

            Label {
                Layout.fillWidth: true
                font.pixelSize: 20
                color: "white"
            }

            TextField {
                id: filter
                Layout.alignment: Qt.AlignTop
                implicitHeight: 39
                visible: mainViewManger.currentIndex == 2 && HumbleApi.isLoggedIn()
                onTextChanged: {
                    pageBundles.filterList(filter.text);
                }
            }

            ToolButton {
                text: "‹"
                Layout.alignment: Qt.AlignTop
                implicitHeight: 39
                visible: mainViewManger.currentIndex > 0 && mainViewManger.currentIndex != 2
                onClicked: {
                    if(mainViewManger.currentIndex == 3) mainViewManger.currentIndex = 2
                    if(mainViewManger.currentIndex == 1) mainViewManger.currentIndex = 0
                    if(mainViewManger.currentIndex == 4) mainViewManger.currentIndex = 3
                }
            }

            ToolButton {
                text: qsTr("Log Out")
                Layout.alignment: Qt.AlignTop
                implicitHeight: 39
                visible: mainViewManger.currentIndex > 1
                onClicked: {
                    mainViewManger.currentIndex = 0
                }
            }
        }
    }

    StackLayout {
        id: mainViewManger
        anchors.fill: parent
        currentIndex: 0

        PageLogin {
            id: pageLogin
        }

        PageCaptcha {
            id: pageCaptcha
            onReCaptchaEntered: {
                mainViewManger.currentIndex = 0
                pageLogin.recaptcha_response = response;
                pageLogin.captchaFound();
            }
        }

        PageBundles {
            id: pageBundles
        }

        PageProducts {
            id: pageProducts
        }

        PageDownloads {
            id: pageDownloads
        }
    }
}
