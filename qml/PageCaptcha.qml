import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtWebView 1.1
ColumnLayout {
    id:captchaPage
    Layout.fillHeight: true
    Layout.fillWidth: true
    signal reCaptchaEntered(string challenge, string response)
    WebView {
        id: webview
        Layout.fillWidth: true
        Layout.fillHeight: true
        url: "https://hr-humblebundle.appspot.com/user/captcha"
        onLoadingChanged: {
            if(loadRequest.status === WebView.LoadSucceededStatus) {
                webview.runJavaScript("window.Android={setCaptchaResponse:function(challenge,response){window.Android.recap='qhumble|'+challenge+'|'+response}};");
            }
        }
    }

    Button {
        id:submit
        Layout.alignment: Qt.AlignHCenter
        text: qsTr("Click After Submitting")
        onClicked: {
            webview.runJavaScript("window.Android.recap",function(value){
                var a = value.split("|")
                var challenge = a[1];
                var response  = a[2];
                captchaPage.reCaptchaEntered("",response);
            }
            );
        }
    }
}
