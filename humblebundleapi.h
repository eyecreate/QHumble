#pragma once

#include <QObject>
#include "humbledb.h"
#include <QSqlQueryModel>

class QNetworkAccessManager;
class QNetworkReply;

class HumbleBundleAPI : public QObject
{
    Q_OBJECT
public:
    HumbleBundleAPI();

    Q_INVOKABLE void setCredentials(const QString & login, const QString & password, const QString & twoFactor, const QString & reCaptchaResponse);
    Q_INVOKABLE void updateOrderList();

    Q_INVOKABLE bool isLoggedIn() { return isLoggedIn_; }
    Q_INVOKABLE bool isRefreshNeeded();

    Q_INVOKABLE void updateOrder(const QString & orderId);
    Q_INVOKABLE QVariant purchaseModel();
    Q_INVOKABLE QVariant productsModel(int purchaseId);
    Q_INVOKABLE QVariant productPlatforms(int product);

signals:
	void orderListUpdated();
    void loginSucceeded();
    void loginError(const QString & error);
	void error(const QString & error);

private slots:
	void onFinished(QNetworkReply * reply);

private:
	void login();

    void parseOrderList(const QByteArray & json);
    void parseProductList(const QByteArray & json);
    void completedParsingOnePurchase();

    HumbleDB db;

private:
	QString username_;
	QString password_;
    QString twoFactor_;
    QString reCaptcha_;
    int refreshCounter = 0;

	QNetworkAccessManager * networkAccessManager_;
	bool isLoggedIn_;
};
