import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Humble Bundle")

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            Button {
                text: qsTr("Back")
                onClicked: mainViewManger.currentIndex = 0
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
