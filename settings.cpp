#include "settings.h"

#include <QStandardPaths>
#include <QSettings>

QVariant SettingsBase::readEntry(const QString &key, const QVariant defaultValue)
{
    QSettings settings("QHumble", "QHumble");
    return settings.value(key, defaultValue);
}

void SettingsBase::writeEntry(const QString &key, const QVariant &value)
{
    QSettings settings("QHumble", "QHumble");
    settings.setValue(key, value);
}


Settings::Settings(QObject *parent)
    :
      QObject(parent)
{
}

QString Settings::getSessionToken()
{
    return readEntry("token","").toString();
}

void Settings::setSessionToken(const QString & token)
{
    writeEntry("token", token);
}
