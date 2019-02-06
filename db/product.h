#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    explicit Product();
    int getId();
    QString getIntName();
    QString getHumanName();
    QString getIconURL();
    int getPurchaseId();
    void setId(int id);
    void setIntName(QString intName);
    void setHumanName(QString humanName);
    void setIconURL(QString iconURL);
    void setPurchaseId(int id);
private:
    int id;
    QString intName;
    QString humanName;
    QString iconURL;
    int purchaseId;
};

#endif // PRODUCT_H
