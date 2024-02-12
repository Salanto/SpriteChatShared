#include "coordinatoradvertiser.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

CoordinatorAdvertiser::CoordinatorAdvertiser(QObject *parent, const QString &f_user_agent, bool f_enabled) :
    QObject{parent},
    user_agent{f_user_agent}
{
    http = new QNetworkAccessManager(this);
    connect(http, &QNetworkAccessManager::finished, this, &CoordinatorAdvertiser::finished);
    timeout = new QTimer(this);
    timeout->setInterval(HEARTBEAT);
    connect(timeout, &QTimer::timeout, this, &CoordinatorAdvertiser::advertise);
    if (f_enabled) {
        timeout->start();
        advertise();
    }
}

QString CoordinatorAdvertiser::userAgent() const
{
    return user_agent;
}

void CoordinatorAdvertiser::setEnabled(bool f_enabled)
{
    if (f_enabled) {
        advertise();
        timeout->start();
    }
    else {
        timeout->stop();
    }
}

CoordinatorTypes::ServerInfo *CoordinatorAdvertiser::metaDataRW()
{
    return &serverinfo;
}

void CoordinatorAdvertiser::advertise()
{
    QNetworkRequest req(BASE_URL + "servers");
    req.setHeader(QNetworkRequest::UserAgentHeader, userAgent());
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject body;
    if (!serverinfo.ip.isEmpty()) {
        body["ip"] = serverinfo.ip;
    };
    body["port"] = 65535; // Coordinator/MS3 limitation. TODO: Remove when no longer applicable!
    body["ws_port"] = serverinfo.ws_port;
    body["wss_port"] = serverinfo.wss_port;
    body["name"] = serverinfo.name;
    body["description"] = serverinfo.description;
    body["players"] = serverinfo.players;

    http->post(req, QJsonDocument(body).toJson(QJsonDocument::Indented));
}

void CoordinatorAdvertiser::finished(QNetworkReply *f_reply)
{
    if (f_reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error encountered:" << f_reply->error();
    }

    int status_code = f_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status_code != 200) {
        qDebug() << "Coordinator error encountered. Statuscode:" << status_code;

        QJsonParseError error;
        QJsonDocument response = QJsonDocument::fromJson(f_reply->readAll(), &error);

        if (error.error != QJsonParseError::NoError) {
            qDebug() << "Invalid JSON response:" << error.errorString();
            f_reply->deleteLater();
            return;
        }
        qDebug() << response;
    }
    f_reply->deleteLater();
}
