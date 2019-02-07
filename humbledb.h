#ifndef HUMBLEDB_H
#define HUMBLEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include "db/purchase.h"
#include "db/product.h"
#include "db/download.h"
#include "db/file.h"
#include <QList>
#include "db/customquerymodel.h"

class HumbleDB : public QObject
{
    Q_OBJECT
public:
    explicit HumbleDB();
    const QString databaseName = "qhumble";
    void clearDB();
    int addPurchase(Purchase purchase);
    int addProduct(Product product);
    int addDownload(Download download);
    int addFile(File file);
    /*Purchase getPurchase(int id);
    Product getProduct(int id);
    Download getDownload(int id);
    File getFile(int id);*/
    int getPurchaseCount();
    QSqlQueryModel *getPurchaseModel();
    /*QList<Purchase> getAllPurchases();
    QList<Product> getProductsForPurchase(int id);
    QList<Download> getDownloadsForProduct(int id);
    QList<File> getFilesForDownload(int id);*/

signals:
    void dbCleared();
    void newDBEntry();
public slots:

private:
    CustomQueryModel purchaseModel;
};

#endif // HUMBLEDB_H
