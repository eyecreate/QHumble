#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>
#include <Table>
#include <TableSet>

class Download;
class Purchase;
class Product : public Nut::Table
{
    Q_OBJECT

    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(int, id, id, setId)
    NUT_NOT_NULL(intname)
    NUT_UNIQUE(intname)
    NUT_DECLARE_FIELD(QString, intname, intName, setIntName)
    NUT_NOT_NULL(humanname)
    NUT_DECLARE_FIELD(QString, humanname, humanName, setHumanName)
    NUT_DECLARE_FIELD(QString, iconurl, iconURL, setIconURL)
    NUT_DECLARE_CHILD_TABLE(Download, downloads)
    NUT_FOREGION_KEY(Purchase, int, purchase, purchase, setPurchase)
public:
    Q_INVOKABLE Product(QObject *parent = nullptr);

signals:

public slots:
};

Q_DECLARE_METATYPE(Product*)

#endif // PRODUCT_H
