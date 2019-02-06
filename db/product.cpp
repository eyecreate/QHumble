#include "product.h"
#include "download.h"

Product::Product()
{
}

int Product::getId()
{
    return id;
}

QString Product::getIntName()
{
    return intName;
}

QString Product::getHumanName()
{
    return humanName;
}

QString Product::getIconURL()
{
    return iconURL;
}

int Product::getPurchaseId()
{
    return purchaseId;
}

void Product::setId(int id)
{
    this->id = id;
}

void Product::setIntName(QString intName)
{
    this->intName = intName;
}

void Product::setHumanName(QString humanName)
{
    this->humanName = humanName;
}

void Product::setIconURL(QString iconURL)
{
    this->iconURL = iconURL;
}

void Product::setPurchaseId(int id)
{
    this->purchaseId = id;
}
