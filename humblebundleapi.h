#pragma once

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class HumbleDownload
{
public:
	QString machine_name;
	QString platform;
	QString url;

	QString toString() const {
		return
		        "machine_name: " + machine_name + "\n" +
		        "platform:     " + platform     + "\n" +
		        "url:          " + url          + "\n"
		        ;
	}
};

class HumbleProduct
{
public:
	QString human_name;
	QString machine_name;
	QString iconUrl;

	QList<HumbleDownload> downloads;

	QString toString() const {
		QString retval =
		        "human_name:   " + human_name   + "\n" +
		        "machine_name: " + machine_name + "\n" +
		        "iconUrl:      " + iconUrl      + "\n"
		        ;
		foreach(const HumbleDownload & download, downloads) {
			retval += "download: " + download.toString();
		}

		return retval;
	}
};

class HumbleOrder
{
public:
	HumbleOrder() : isBundle(false) {}

	QString toString () const {
		return
		        "isBundle: "   + QString::number((int) isBundle) + "\n" +
		        "human_name: " + human_name                      + "\n" +
		        "orderId: "    + orderId                         + "\n"
		        ;
	}

public:
	bool isBundle;
	QString human_name;
	QString orderId;
};

class HumbleBundleAPI : public QObject
{
    Q_OBJECT
public:
    HumbleBundleAPI();

    Q_INVOKABLE void setCredentials(const QString & login, const QString & password, const QString & twoFactor, const QString & reCaptchaResponse);
    Q_INVOKABLE void updateOrderList();

    Q_INVOKABLE bool isLoggedIn() { return isLoggedIn_; }

    Q_INVOKABLE void updateOrder(const QString & orderId);

signals:
	void orderListUpdated();
    void loginSucceeded();
    void loginError(const QString & error);
	void error(const QString & error);

private slots:
	void onFinished(QNetworkReply * reply);

private:
	void login();

	QList<HumbleOrder> parseOrderList(const QByteArray & json);
	QList<HumbleProduct> parseProductList(const QByteArray & json);

private:
	QString username_;
	QString password_;
    QString twoFactor_;
    QString reCaptcha_;

	QNetworkAccessManager * networkAccessManager_;
	bool isLoggedIn_;
};
