#include "settings.h"

#include <QStandardPaths>
#include <QSettings>

QVariant SettingsBase::readEntry(const QString &key, const QVariant defaultValue)
{
    QSettings settings("CMon", "QPod");
    return settings.value(key, defaultValue);
}

void SettingsBase::writeEntry(const QString &key, const QVariant &value)
{
    QSettings settings("CMon", "QPod");
    settings.setValue(key, value);
}


Settings::Settings(QObject *parent)
    :
      QObject(parent)
{
}

QString Settings::getUsername()
{
	return readEntry("username", "").toString();
}

void Settings::setUsername(const QString & username)
{
	writeEntry("username", username);
}

QString Settings::getPassword()
{
	return readEntry("password", "").toString();
}

void Settings::setPassword(const QString & password)
{
	writeEntry("password", password);
}

QString Settings::getSessionToken()
{
    return readEntry("token","").toString();
}

void Settings::setSessionToken(const QString & token)
{
    writeEntry("token", token);
}
