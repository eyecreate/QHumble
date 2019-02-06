#include "download.h"
#include "file.h"

Download::Download()
{
}

int Download::getId()
{
    return id;
}

QString Download::getIntName()
{
    return intName;
}

QString Download::getPlatform()
{
    return platform;
}

int Download::getProductId()
{
    return productId;
}

void Download::setId(int id)
{
    this->id = id;
}

void Download::setIntName(QString intName)
{
    this->intName = intName;
}

void Download::setPlatform(QString platform)
{
    this->platform = platform;
}

void Download::setProductId(int id)
{
    this->productId = id;
}
