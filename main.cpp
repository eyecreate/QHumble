#include <humblebundleapi.h>

#include "settings.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    Settings settings;
    HumbleBundleAPI hbApi;

	QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("HumbleApi", &hbApi);
    engine.rootContext()->setContextProperty("purchaseModel",hbApi.purchaseModel());

	engine.rootContext()->setContextProperty("Settings", &settings);

	engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

	return app.exec();
}
