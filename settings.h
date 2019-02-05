#pragma once

#include <QObject>
#include <QVariant>

class SettingsBase
{
public:
	static QVariant readEntry(const QString & key, const QVariant defaultValue = QVariant());
	static void writeEntry(const QString & key, const QVariant & value);
};

class Settings : public QObject, public SettingsBase
{
	Q_OBJECT

public:
	Settings(QObject * parent = 0);

    Q_INVOKABLE static QString getSessionToken();
    Q_INVOKABLE static void setSessionToken(const QString & token);
};
