#ifndef PURCHASE_H
#define PURCHASE_H

#include <QString>

class Purchase
{
public:
    explicit Purchase();
    int getId();
    QString getType();
    QString getHumanName();
    QString getIntName();
    QString getHumbleId();
    void setId(int id);
    void setType(QString type);
    void setHumanName(QString humanName);
    void setIntName(QString intName);
    void setHumbleId(QString humbleId);

private:
    int id;
    QString type;
    QString humanName;
    QString intName;
    QString humbleId;
};

#endif // PURCHASE_H
