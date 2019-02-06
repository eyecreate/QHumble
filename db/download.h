#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QString>

class Download
{
public:
    explicit Download();
    int getId();
    QString getIntName();
    QString getPlatform();
    int getProductId();
    void setId(int id);
    void setIntName(QString intName);
    void setPlatform(QString platform);
    void setProductId(int id);

private:
    int id;
    QString intName;
    QString platform;
    int productId;
};

#endif // DOWNLOAD_H
