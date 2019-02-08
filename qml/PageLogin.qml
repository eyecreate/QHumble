import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    id: pageLoginRect
    width: 62
    height: 100

    Connections {
        target: HumbleApi
        onLoginSucceeded: {
            pageLoginRect.loading = false;
            errorText.visible = false;
            mainViewManger.currentIndex = 2;
            pageBundles.startUpdate();
        }
        onLoginError: {
            mainViewManger.currentIndex = 0;
            errorText.visible = true;
            errorText.text = error;
        }
    }

    Component.onCompleted: {
        if(HumbleApi.isLoggedIn()){
            mainViewManger.currentIndex = 2;
        }
    }

    property bool loading: false
    property string recaptcha_challenge: ""
    property string recaptcha_response: ""

    function login(username, password, captchaResponse) {
        pageLoginRect.loading = true;
        errorText.visible = false;

        if(twoFactorInput.length == 0) {
            HumbleApi.setCredentials(username, password,"", captchaResponse);
        }
        else {
            HumbleApi.setCredentials(username, password, twoFactorInput.text, captchaResponse);
        }
    }

    function captchaFound() {
        login(loginInput.text, passwordInput.text, recaptcha_response);
    }

    Grid {
        id: grid
        y: 20

        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 5

        Label {
            text: qsTr("Login:")
        }
        TextField {
            id: loginInput
        }

        Label {
            text: qsTr("Password:")
        }
        TextField {
            id: passwordInput
            echoMode: TextInput.Password
        }

        Label {
            text: qsTr("2-Factor Code:")
        }
        TextField {
            id: twoFactorInput
        }
    }

    Button {
        id: loginButton
        enabled: loginInput.text != "" && passwordInput.text != ""
        text: qsTr("Login")
        anchors.right: grid.right
        anchors.top: grid.bottom
        onClicked: mainViewManger.currentIndex = 1
    }

    Rectangle {
        anchors.right: grid.right
        anchors.left: grid.left
        anchors.top: loginButton.bottom

        Text {
            id: errorText
            anchors.right: parent.right
            text: qsTr("Login in failed.")
            color: "#ff0000"
            visible: false
        }

        Loading {
            width: 20
            height: 20
            anchors.left: errorText.left
            visible: pageLoginRect.loading
        }
    }
}
