#include "humbledb.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

HumbleDB::HumbleDB(QObject *parent):QObject (parent)
{
    //Initialize DB for future connections.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",databaseName);
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString file = QDir(dbPath).filePath("humbleDB.db");
    qDebug() << "DB location:" << file;
    db.setDatabaseName(file);
    if(!db.open()) qDebug() << "Error opening DB.";
    else
    {
        //Create if tables don't exist
        db.exec("CREATE TABLE IF NOT EXISTS `Purchase` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `type` TEXT NOT NULL, `humanname` TEXT NOT NULL, `intname` TEXT, `humbleid` TEXT NOT NULL UNIQUE );");
        db.exec("CREATE TABLE IF NOT EXISTS `Product` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `intname` TEXT NOT NULL, `humanname` TEXT NOT NULL, `iconurl` TEXT, `purchase` INTEGER, FOREIGN KEY(`purchase`) REFERENCES `Purchase`(`id`) );");
        db.exec("CREATE TABLE IF NOT EXISTS `Download` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `intname` TEXT NOT NULL, `platform` TEXT NOT NULL, `product` INTEGER, FOREIGN KEY(`product`) REFERENCES `Product`(`id`) );");
        db.exec("CREATE TABLE IF NOT EXISTS `File` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT NOT NULL, `filesize` INTEGER, `md5` TEXT, `weburl` TEXT, `bittorrenturl` TEXT, `download` INTEGER, FOREIGN KEY(`download`) REFERENCES `Download`(`id`) );");
    }
}

void HumbleDB::clearDB()
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    db.exec("DELETE FROM `File`");
    db.exec("DELETE FROM `Download`");
    db.exec("DELETE FROM `Product`");
    db.exec("DELETE FROM `Purchase`");
    emit dbCleared();
}

int HumbleDB::addPurchase(Purchase purchase)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO `Purchase` (`type`,`humanname`,`intname`,`humbleid`) VALUES (:type,:humanname,:intname,:humbleid)");
    query.bindValue(":type",purchase.getType());
    query.bindValue(":humanname",purchase.getHumanName());
    query.bindValue(":intname",purchase.getIntName());
    query.bindValue(":humbleid",purchase.getHumbleId());
    query.exec();
    emit newDBEntry();
    return query.lastInsertId().toInt();
}

int HumbleDB::addProduct(Product product)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO `Product` (`intname`,`humanname`,`iconurl`,`purchase`) VALUES (:intname,:humanname,:iconurl,:purchase)");
    query.bindValue(":intname",product.getIntName());
    query.bindValue(":humanname",product.getHumanName());
    query.bindValue(":iconurl",product.getIconURL());
    query.bindValue(":purchase",product.getPurchaseId());
    query.exec();
    emit newDBEntry();
    return query.lastInsertId().toInt();
}

int HumbleDB::addDownload(Download download)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO `Download` (`intname`,`platform`,`product`) VALUES (:intname,:platform,:product)");
    query.bindValue(":intname",download.getIntName());
    query.bindValue(":platform",download.getPlatform());
    query.bindValue(":product",download.getProductId());
    query.exec();
    emit newDBEntry();
    return query.lastInsertId().toInt();
}

int HumbleDB::addFile(File file)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("INSERT INTO `File` (`name`,`filesize`,`md5`,`weburl`,`bittorrenturl`,`download`) VALUES (:name,:filesize,:md5,:weburl,:bturl,:download)");
    query.bindValue(":name",file.getName());
    query.bindValue(":filesize",file.getFileSize());
    query.bindValue(":md5",file.getMD5());
    query.bindValue(":weburl",file.getWebURL());
    query.bindValue(":bturl",file.getBitTorrentURL());
    query.bindValue(":download",file.getDownloadId());
    query.exec();
    emit newDBEntry();
    return query.lastInsertId().toInt();
}

void HumbleDB::updatePurchase(Purchase purchase)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("UPDATE `Purchase` SET type = :type,humanname = :humanname,intname = :intname,humbleid = :humbleid WHERE intname = "+purchase.getIntName());
    query.bindValue(":type",purchase.getType());
    query.bindValue(":humanname",purchase.getHumanName());
    query.bindValue(":intname",purchase.getIntName());
    query.bindValue(":humbleid",purchase.getHumbleId());
    query.exec();
}

void HumbleDB::updateProduct(Product product)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("UPDATE `Product` SET intname = :intname,humanname = :humanname,iconurl = :iconurl,purchase = :purchase WHERE intname = "+product.getIntName());
    query.bindValue(":intname",product.getIntName());
    query.bindValue(":humanname",product.getHumanName());
    query.bindValue(":iconurl",product.getIconURL());
    query.bindValue(":purchase",product.getPurchaseId());
    query.exec();
}

void HumbleDB::updateDownload(Download download)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("UPDATE `Download` SET intname = :intname,platform = :platform,product = :product WHERE intname = "+download.getIntName());
    query.bindValue(":intname",download.getIntName());
    query.bindValue(":platform",download.getPlatform());
    query.bindValue(":product",download.getProductId());
    query.exec();
}

int HumbleDB::getPurchaseCount()
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM `Purchase`");
    query.exec();
    if(query.next())
    {
        return query.value(0).toInt();
    }
    return 0;
}

int HumbleDB::purchaseExists(Purchase purchase)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("SELECT id FROM `Purchase` WHERE Purchase.intname = '"+purchase.getIntName()+"' AND Purchase.humbleid = '"+purchase.getHumbleId()+"'");
    query.exec();
    if(query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

int HumbleDB::productExists(Product product)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("SELECT id FROM `Product` WHERE Product.intname = '"+product.getIntName()+"' AND Product.purchase = "+QString::number(product.getPurchaseId()));
    query.exec();
    if(query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

int HumbleDB::downloadExists(Download download)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("SELECT id FROM `Download` WHERE Download.intname = '"+download.getIntName()+"' AND Download.product = '"+QString::number(download.getProductId())+"'");
    query.exec();
    if(query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

void HumbleDB::eraseFilesForDownload(int download)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    db.exec("DELETE FROM `File` WHERE download = "+QString::number(download));
}

QSqlQueryModel *HumbleDB::getPurchaseModel()
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQueryModel *model = new CustomQueryModel(this);
    model->setQuery("SELECT * FROM `Purchase`",db);
    return model;
}

QSqlQueryModel *HumbleDB::getProductModel(int purchaseId)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQueryModel *model = new CustomQueryModel(this);
    model->setQuery("SELECT * FROM `Product` WHERE Product.purchase = "+QString::number(purchaseId),db);
    return model;
}

QSqlQueryModel *HumbleDB::getProductPlatforms(int product)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQueryModel *model = new CustomQueryModel(this);
    model->setQuery("SELECT DISTINCT platform FROM `Download` WHERE Download.product = "+QString::number(product),db);
    return model;
}

QSqlQueryModel *HumbleDB::getDownloadModel(int product)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQueryModel *model = new CustomQueryModel(this);
    model->setQuery("SELECT * FROM `Download` WHERE Download.product = "+QString::number(product),db);
    return model;
}

QSqlQueryModel *HumbleDB::getFileModel(int download)
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQueryModel *model = new CustomQueryModel(this);
    model->setQuery("SELECT * FROM `File` WHERE File.download = "+QString::number(download),db);
    return model;
}

QSortFilterProxyModel *HumbleDB::getFilterablePurchaseModel()
{
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQueryModel *model = new CustomQueryModel(this);
    model->setQuery("SELECT * FROM `Purchase`",db);
    QSortFilterProxyModel *filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(model);
    return filterModel;
}
