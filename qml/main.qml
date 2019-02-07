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
                text: qsTr("Humble Bundle")
                font.pixelSize: 20
                color: "white"
            }

            ToolButton {
                text: qsTr("Log Out")
                anchors.top: parent.top
                implicitHeight: 39
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
    }
}
