#ifndef PURCHASE_H
#define PURCHASE_H

#include <QObject>
#include <Table>
#include <TableSet>

class Product;
class Purchase : public Nut::Table
{
    Q_OBJECT

    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(int, id, id, setId)
    NUT_NOT_NULL(type)
    NUT_DECLARE_FIELD(QString, type, type, setType)
    NUT_NOT_NULL(humanname)
    NUT_DECLARE_FIELD(QString, humanname, humanName, setHumanName)
    NUT_DECLARE_FIELD(QString, intname, intName, setIntName)
    NUT_NOT_NULL(humbleid)
    NUT_UNIQUE(humbleid)
    NUT_DECLARE_FIELD(QString, humbleid, humbleId, setHumbleId)
    NUT_DECLARE_CHILD_TABLE(Product, products)
public:
    Q_INVOKABLE Purchase(QObject *parent = nullptr);

signals:

public slots:
};

Q_DECLARE_METATYPE(Purchase*)

#endif // PURCHASE_H
