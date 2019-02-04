import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    toolBar: ToolBar {
        height: 70
        Button {
            text: qsTr("Back")
            onClicked: mainViewManger.previousView()
            height: 70
        }
    }

    SimpleViewManager {
        id: mainViewManger
        anchors.fill: parent
        color: "#343434"

        PageLogin {
            id: pageLogin
            anchors.fill: parent
        }

        PageCaptcha {
            id: pageCaptcha
            onReCaptchaEntered: {
                pageCaptcha.visible = false;
                pageLogin.recaptcha_challenge = challenge;
                pageLogin.recaptcha_response = response;
                pageLogin.captchaFound();
            }

            anchors.fill: parent
        }

        PageBundles {
            id: pageBundles
            anchors.fill: parent
        }
    }
}
