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

/*Purchase HumbleDB::getPurchase(int id)
{
    //TODO
}

Product HumbleDB::getProduct(int id)
{
    //TODO
}

Download HumbleDB::getDownload(int id)
{
    //TODO
}

File HumbleDB::getFile(int id)
{
    //TODO
}*/

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

/*QList<Purchase> HumbleDB::getAllPurchases()
{
    QList<Purchase> purchases;
    QSqlDatabase db = QSqlDatabase::database(databaseName);
    QSqlQuery query(db);
    query.prepare("SELECT * FROM `Purchase`");
    query.exec();
    while(query.next())
    {
        Purchase purchase;
        purchase.setId(query.value("id").toInt());
        purchase.setType(query.value("type").toString());
        purchase.setIntName(query.value("intname").toString());
        purchase.setHumanName(query.value("humanname").toString());
        purchase.setHumbleId(query.value("humbleid").toString());
        purchases.append(purchase);
    }
    return purchases;
}

QList<Product> HumbleDB::getProductsForPurchase(int id)
{
    //TODO
}

QList<Download> HumbleDB::getDownloadsForProduct(int id)
{
    //TODO
}

QList<File> HumbleDB::getFilesForDownload(int id)
{
    //TODO
}*/
