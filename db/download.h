#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <Table>
#include <TableSet>

class File;
class Product;
class Download : public Nut::Table
{
    Q_OBJECT

    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(int, id, id, setId)
    NUT_UNIQUE(intname)
    NUT_DECLARE_FIELD(QString, intname, intName, setIntName)
    NUT_NOT_NULL(platform)
    NUT_DECLARE_FIELD(QString, platform, platform, setPlatform)
    NUT_DECLARE_CHILD_TABLE(File, files)
    NUT_FOREGION_KEY(Product, int, product, product, setProduct)
public:
    Q_INVOKABLE Download(QObject *parent = nullptr);

signals:

public slots:
};

Q_DECLARE_METATYPE(Download*)

#endif // DOWNLOAD_H
