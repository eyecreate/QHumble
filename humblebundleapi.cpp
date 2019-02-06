#include "humblebundleapi.h"

#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <settings.h>
#include "db/purchase.h"
#include "db/product.h"
#include "db/download.h"
#include "db/file.h"

#include <QDebug>

namespace URLS {

const QString apiBaseUrl         = "https://hr-humblebundle.appspot.com/api/v1/";
const QString loginUrl           = "https://hr-humblebundle.appspot.com/processlogin";
const QString orderListUrl       = apiBaseUrl + "user/order"           ;
const QString orderUrl           = apiBaseUrl + "order/%1"             ; // %1 is the order_id
//const QString claimedEntitiesUrl = apiBaseUrl + "user/claimed/entities";
//const QString signedDownloadUrl  = apiBaseUrl + "user/Download/%1/sign"; // %1 is the machine_name

}

HumbleBundleAPI::HumbleBundleAPI()
    :
      networkAccessManager_(new QNetworkAccessManager(this)),
      isLoggedIn_(false)
{
	connect(networkAccessManager_, &QNetworkAccessManager::finished, this, &HumbleBundleAPI::onFinished);
    if(Settings::getSessionToken().size() > 0) {
        isLoggedIn_ = true;
        //networkAccessManager_->cookieJar()->insertCookie(QNetworkCookie("_simpleauth_sess",Settings::getSessionToken().toLatin1()));
    }
}

void HumbleBundleAPI::setCredentials(const QString & login, const QString & password, const QString & twoFactor = "", const QString & reCaptchaResponse = "")
{
	username_ = login;
	password_ = password;
    twoFactor_ = twoFactor;
    reCaptcha_ = reCaptchaResponse;

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
    request.setRawHeader("X-Requested-By",  "hb_android_app");
    request.setHeader(QNetworkRequest::CookieHeader,QVariant::fromValue(QNetworkCookie("_simpleauth_sess",Settings::getSessionToken().toLatin1())));

    networkAccessManager_->get(request);
}

bool HumbleBundleAPI::isRefreshNeeded()
{
    if(db.getPurchaseCount() > 0)
    {
        return false;
    }
    return true;
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
    request.setRawHeader("X-Requested-By",  "hb_android_app");
    request.setHeader(QNetworkRequest::CookieHeader,QVariant::fromValue(QNetworkCookie("_simpleauth_sess",Settings::getSessionToken().toLatin1())));

	networkAccessManager_->get(request);
}

void HumbleBundleAPI::login()
{
	QUrlQuery queryUrl;
	queryUrl.addQueryItem("ajax", "true");

	queryUrl.addQueryItem("username", username_);
	queryUrl.addQueryItem("password", password_);
    if(twoFactor_.size() > 0) {
        queryUrl.addQueryItem("code", twoFactor_);
    }
    queryUrl.addQueryItem("recaptcha_response_field", reCaptcha_);
    queryUrl.addQueryItem("recaptcha_challenge_field","");

	QNetworkRequest request;
	request.setUrl(QUrl(URLS::loginUrl));
	request.setRawHeader("Accept",         "application/json");
	request.setRawHeader("Accept-Charset", "utf-8");
	request.setRawHeader("Keep-Alive",     "true");
	request.setRawHeader("content-type",   "application/x-www-form-urlencoded");
    request.setRawHeader("X-Requested-By",  "hb_android_app");

	networkAccessManager_->post(request, queryUrl.toString(QUrl::FullyEncoded).toUtf8());
}

void HumbleBundleAPI::parseOrderList(const QByteArray & json)
{
    //delete DB. TODO: eventually find a good way to only update entries when refreshing.
    db.clearDB();
    //Retrieve details of each purchase and add them to the DB.

	QJsonDocument jDoc = QJsonDocument::fromJson(json);
	QJsonArray array = jDoc.array();
    refreshCounter = array.size();
	for (int i = 0; i < array.size(); ++i) {
		QJsonObject object = array[i].toObject();
        updateOrder(object["gamekey"].toString());
    }
}

void HumbleBundleAPI::parseProductList(const QByteArray & json)
{

	QJsonDocument jDoc = QJsonDocument::fromJson(json);
	QJsonObject object = jDoc.object();

    bool newDBEntry = true;

    //TODO: Check if DB entry exists. If so, update, otherwise, add new one.
    Purchase purchase;

    purchase.setType(object["product"].toObject()["category"].toString());
    purchase.setIntName(object["product"].toObject()["machine_name"].toString());
    purchase.setHumanName(object["product"].toObject()["human_name"].toString());
    purchase.setHumbleId(object["gamekey"].toString());

    if(newDBEntry) db.addPurchase(purchase);

    //Seperate Purchase into products
	QJsonArray  subProducts = object["subproducts"].toArray();

	for (int i = 0; i < subProducts.size(); ++i) {
        bool newProductEntry = true;
        QJsonObject jsonProduct = subProducts[i].toObject();

        //TODO: Check if DB entry exists. If so, update, otherwise, add new one.
        Product product;

        product.setIconURL(jsonProduct["icon"].toString());
        product.setHumanName(jsonProduct["human_name"].toString());
        product.setIntName(jsonProduct["machine_name"].toString());
        product.setPurchaseId(purchase.getId());

        //Check if product matches valid product to add to DB.
        if(jsonProduct["downloads"].toArray().size() == 0 || jsonProduct["library_family_name"].toString() == "hidden") {
            continue;
        }

        if(newProductEntry) db.addProduct(product);

		QJsonArray downloadArray = jsonProduct["downloads"].toArray();
		for (int j = 0; j < downloadArray.size(); ++j) {
            bool newDownloadEntry = true;
            QJsonObject jsonDownload = downloadArray[j].toObject();

            //TODO: Check if DB entry exists. If so, update, otherwise, add new one.
            Download download;

            download.setIntName(jsonDownload["machine_name"].toString());
            download.setPlatform(jsonDownload["platform"].toString());
            download.setProductId(product.getId());

            if(newDownloadEntry) db.addDownload(download);

            QJsonArray fileArray = jsonDownload["download_struct"].toArray();
            for(int k = 0; k < fileArray.size(); ++k) {
                QJsonObject jsonFile = fileArray[k].toObject();
                File file;
                file.setMD5(jsonFile["md5"].toString());
                file.setName(jsonFile["name"].toString());
                file.setWebURL(jsonFile["url"].toObject()["web"].toString());
                file.setBitTorrentURL(jsonFile["url"].toObject()["bittorrent"].toString());
                file.setFileSize(jsonFile["file_size"].toInt());
                file.setDownloadId(download.getId());

                db.addFile(file);
            }
		}
    }

    completedParsingOnePurchase();
}

void HumbleBundleAPI::completedParsingOnePurchase()
{
    refreshCounter--;
    if(refreshCounter <= 0) {
        emit orderListUpdated();
    }
}

void HumbleBundleAPI::onFinished(QNetworkReply * reply)
{
	const QString requestUrl = reply->url().toString();
	const bool loggedInReply  = requestUrl.startsWith(URLS::loginUrl);
	const bool orderListReply = requestUrl.startsWith(URLS::orderListUrl);
	const bool orderReply     = requestUrl.startsWith(URLS::orderUrl.arg(""));

	if (reply->error() != QNetworkReply::NoError) {
        if (loggedInReply || reply->error() == QNetworkReply::AuthenticationRequiredError) {
            isLoggedIn_ = false;
            emit loginError(reply->url().toString() +"error(" + reply->error() +"): " + reply->errorString() + "content: " + reply->readAll());
        }
		qDebug() << reply->url() << "error(" << reply->error() <<"): " << reply->errorString() << "content: " << reply->readAll();
		return;
	}

	if (loggedInReply) {
		isLoggedIn_ = true;
        //Find session token
        for (const QNetworkCookie & cookie:networkAccessManager_->cookieJar()->cookiesForUrl(requestUrl)) {
            if(cookie.name() == "_simpleauth_sess") {
                QString editedCookie = cookie.value();
                editedCookie = editedCookie.replace("\"","");
                editedCookie = editedCookie.replace("\\075","=");
                Settings::setSessionToken(editedCookie);
            }
        }
        emit loginSucceeded();
	} else if (orderListReply) {
        qDebug() << "Updating purchase list.";
        parseOrderList(reply->readAll());
	} else if (orderReply) {
        qDebug() << "Updating product";
        parseProductList(reply->readAll());
	} else {
//		qDebug() << reply->url() << reply->readAll();
	}
}
