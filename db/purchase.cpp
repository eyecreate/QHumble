#include "purchase.h"

Purchase::Purchase()
{
}

int Purchase::getId()
{
    return id;
}

QString Purchase::getType()
{
    return type;
}

QString Purchase::getHumanName()
{
    return humanName;
}

QString Purchase::getIntName()
{
    return intName;
}

QString Purchase::getHumbleId()
{
    return humbleId;
}

void Purchase::setId(int id)
{
    this->id = id;
}

void Purchase::setType(QString type)
{
    this->type = type;
}

void Purchase::setHumanName(QString humanName)
{
    this->humanName = humanName;
}

void Purchase::setIntName(QString intName)
{
    this->intName = intName;
}

void Purchase::setHumbleId(QString humbleId)
{
    this->humbleId = humbleId;
}
