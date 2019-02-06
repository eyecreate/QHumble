#include "file.h"

File::File()
{
}

int File::getId()
{
    return id;
}

QString File::getName()
{
    return name;
}

int File::getFileSize()
{
    return filesize;
}

QString File::getMD5()
{
    return md5;
}

QString File::getWebURL()
{
    return webUrl;
}

QString File::getBitTorrentURL()
{
    return bitTorrentUrl;
}

int File::getDownloadId()
{
    return downloadId;
}

void File::setId(int id)
{
    this->id = id;
}

void File::setName(QString name)
{
    this->name = name;
}

void File::setFileSize(int filesize)
{
    this->filesize = filesize;
}

void File::setMD5(QString md5)
{
    this->md5 = md5;
}

void File::setWebURL(QString webUrl)
{
    this->webUrl = webUrl;
}

void File::setBitTorrentURL(QString bitTorrentUrl)
{
    this->bitTorrentUrl = bitTorrentUrl;
}

void File::setDownloadId(int id)
{
    this->downloadId = id;
}
