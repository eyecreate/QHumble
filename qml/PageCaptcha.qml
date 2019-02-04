import QtQuick 2.0
import QtWebEngine 1.8
WebEngineView {
    id: webview
    url: "https://hr-humblebundle.appspot.com/user/captcha"
    anchors.fill: parent

    signal reCaptchaEntered(string challenge, string response)

    onJavaScriptConsoleMessage: {
        if(message.substring(0,7) == "qhumble") {
            var a = message.split("|")
            var challenge = a[1];
            var response  = a[2];
            webview.reCaptchaEntered(challenge, response);
        }
    }
    userScripts: [
        WebEngineScript {
            sourceUrl:  Qt.resolvedUrl("assets/js/CaptchaInjection.js")
            injectionPoint: WebEngineScript.Deferred
            worldId: WebEngineScript.MainWorld
        }
    ]
}
