#ifndef HUMBLEDB_H
#define HUMBLEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <Database>

class Purchase;
class Product;
class Download;
class File;
class HumbleDB : public Nut::Database
{
    Q_OBJECT

    NUT_DB_VERSION(1)

    NUT_DECLARE_TABLE(Purchase, purchases)
    NUT_DECLARE_TABLE(Product, products)
    NUT_DECLARE_TABLE(Download, downloads)
    NUT_DECLARE_TABLE(File, files)
public:
    explicit HumbleDB();

signals:

public slots:

private:
};

#endif // HUMBLEDB_H
