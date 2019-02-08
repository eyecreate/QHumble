#include <humblebundleapi.h>

#include "settings.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebView>

#ifdef Q_OS_ANDROID
#include <QtSvg>    //Because deployment sometimes just forgets to include this lib otherwise
#endif

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QtWebView::initialize();

    Settings settings;
    HumbleBundleAPI hbApi;

	QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("HumbleApi", &hbApi);

	engine.rootContext()->setContextProperty("Settings", &settings);

	engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

	return app.exec();
}
