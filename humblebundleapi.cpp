#include "humblebundleapi.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>

namespace URLS {

const QString apiBaseUrl         = "https://hr-humblebundle.appspot.com/api/v1/";
const QString loginUrl           = "https://hr-humblebundle.appspot.com/processlogin";
const QString orderListUrl       = apiBaseUrl + "user/order"           ;
const QString orderUrl           = apiBaseUrl + "order/%1"             ; // %1 is the order_id
const QString claimedEntitiesUrl = apiBaseUrl + "user/claimed/entities";
const QString signedDownloadUrl  = apiBaseUrl + "user/Download/%1/sign"; // %1 is the machine_name

}

HumbleBundleAPI::HumbleBundleAPI()
    :
      networkAccessManager_(new QNetworkAccessManager(this)),
      isLoggedIn_(false)
{
	connect(networkAccessManager_, &QNetworkAccessManager::finished, this, &HumbleBundleAPI::onFinished);
}

void HumbleBundleAPI::setCredentials(const QString & login, const QString & password)
{
	username_ = login;
	password_ = password;

	this->login();
}

void HumbleBundleAPI::updateOrderList()
{
	QUrlQuery queryUrl;
	queryUrl.addQueryItem("ajax", "true");

	QUrl url(URLS::orderListUrl);
	url.setQuery(queryUrl);
	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader("Accept",         "application/json");
	request.setRawHeader("Accept-Charset", "utf-8");
	request.setRawHeader("Keep-Alive",     "true");

	networkAccessManager_->get(request);
}

void HumbleBundleAPI::updateOrder(const QString & orderId)
{
	QUrlQuery queryUrl;
	queryUrl.addQueryItem("ajax", "true");

	QUrl url(URLS::orderUrl.arg(orderId));
	url.setQuery(queryUrl);
	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader("Accept",         "application/json");
	request.setRawHeader("Accept-Charset", "utf-8");
	request.setRawHeader("Keep-Alive",     "true");

	networkAccessManager_->get(request);
}

void HumbleBundleAPI::login()
{
	QUrlQuery queryUrl;
	queryUrl.addQueryItem("ajax", "true");

	queryUrl.addQueryItem("username", username_);
	queryUrl.addQueryItem("password", password_);

	QNetworkRequest request;
	request.setUrl(QUrl(URLS::loginUrl));
	request.setRawHeader("Accept",         "application/json");
	request.setRawHeader("Accept-Charset", "utf-8");
	request.setRawHeader("Keep-Alive",     "true");
	request.setRawHeader("content-type",   "application/x-www-form-urlencoded");
    request.setRawHeader("X-Requested-By",  "hb_android_app");

	networkAccessManager_->post(request, queryUrl.toString(QUrl::FullyEncoded).toUtf8());
}

QList<HumbleOrder> HumbleBundleAPI::parseOrderList(const QByteArray & json)
{
	QList<HumbleOrder> orders;

	QJsonDocument jDoc = QJsonDocument::fromJson(json);
	QJsonArray array = jDoc.array();
	for (int i = 0; i < array.size(); ++i) {
		HumbleOrder order;
		QJsonObject object = array[i].toObject();
		order.orderId = object["gamekey"].toString();
		QJsonObject product = object["product"].toObject();
		if (product["category"].toString() == "bundle") {
			order.isBundle = true;
		}
		order.human_name   = product["human_name"].toString();

		orders << order;
	}

	return orders;
}

QList<HumbleProduct> HumbleBundleAPI::parseProductList(const QByteArray & json)
{
	QList<HumbleProduct> products;

	QJsonDocument jDoc = QJsonDocument::fromJson(json);
	QJsonObject object = jDoc.object();
	QJsonArray  subProducts = object["subproducts"].toArray();

	for (int i = 0; i < subProducts.size(); ++i) {
		HumbleProduct product;

		QJsonObject jsonProduct = subProducts[i].toObject();
		product.iconUrl      = jsonProduct["icon"].toString();
		product.human_name   = jsonProduct["human_name"].toString();
		product.machine_name = jsonProduct["machine_name"].toString();

		QJsonArray downloadArray = jsonProduct["downloads"].toArray();
		for (int j = 0; j < downloadArray.size(); ++j) {
			HumbleDownload download;

			QJsonObject jsonDownload = downloadArray[j].toObject();
			download.machine_name = jsonDownload["machine_name"].toString();
			download.platform     = jsonDownload["platform"].toString();
			download.url          = jsonDownload["download_struct"].toArray().first().toObject().value("url").toObject().value("web").toString();

			product.downloads << download;
		}

		products << product;
	}

	return products;
}

void HumbleBundleAPI::onFinished(QNetworkReply * reply)
{
	const QString requestUrl = reply->url().toString();
	const bool loggedInReply  = requestUrl.startsWith(URLS::loginUrl);
	const bool orderListReply = requestUrl.startsWith(URLS::orderListUrl);
	const bool orderReply     = requestUrl.startsWith(URLS::orderUrl.arg(""));

	if (reply->error() != QNetworkReply::NoError) {
		if (loggedInReply) isLoggedIn_ = false;
		qDebug() << reply->url() << "error(" << reply->error() <<"): " << reply->errorString() << "content: " << reply->readAll();
		return;
	}

	if (loggedInReply) {
		isLoggedIn_ = true;
	} else if (orderListReply) {
		QList<HumbleOrder> orders = parseOrderList(reply->readAll());
		foreach(const HumbleOrder & order, orders) {
//			qDebug() << order.toString();
			updateOrder(order.orderId);
		}
	} else if (orderReply) {
		QList<HumbleProduct> products = parseProductList(reply->readAll());
		foreach(const HumbleProduct & product, products) {
			qDebug() << product.toString();
		}
	} else {
//		qDebug() << reply->url() << reply->readAll();
	}
}
