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
#include <QSortFilterProxyModel>

class HumbleDB : public QObject
{
    Q_OBJECT
public:
    explicit HumbleDB(QObject *parent = nullptr);
    const QString databaseName = "qhumble";
    void clearDB();
    int addPurchase(Purchase purchase);
    int addProduct(Product product);
    int addDownload(Download download);
    int addFile(File file);
    int getPurchaseCount();
    QSqlQueryModel *getPurchaseModel();
    QSqlQueryModel *getProductModel(int purchaseId);
    QSqlQueryModel *getProductPlatforms(int product);
    QSqlQueryModel *getDownloadModel(int product);
    QSqlQueryModel *getFileModel(int download);
    QSortFilterProxyModel *getFilterablePurchaseModel();

signals:
    void dbCleared();
    void newDBEntry();
public slots:

private:
};

#endif // HUMBLEDB_H
