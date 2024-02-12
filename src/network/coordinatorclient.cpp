#include "coordinatorclient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

using namespace CoordinatorTypes;

CoordinatorClient::CoordinatorClient(QObject *parent, const QString &f_user_agent, bool playing_advertisement) :
    QObject{parent},
    user_agent{f_user_agent}
{
    http = new QNetworkAccessManager(this);
    playing = new QTimer(this);
    playing->setInterval(PLAYER_HEARTBEAT_TIMEOUT);
    connect(playing, &QTimer::timeout, this, &CoordinatorClient::playingTimeout);
    if (playing_advertisement) {
        playing->start();
    }
}

QString CoordinatorClient::userAgent() const
{
    return user_agent;
}

void CoordinatorClient::requestAll()
{
    requestDocument(SERVERS);
    requestDocument(MOTD);
    requestDocument(VERSION);
    requestDocument(PRIVACY);
}

void CoordinatorClient::requestDocument(DocumentType f_type)
{
    QNetworkRequest request(BASE_URL +
                            QVariant::fromValue(f_type).toString().toLower());
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent());

    QNetworkReply *reply = http->get(request);
    connect(reply, &QNetworkReply::finished, this,
            std::bind(&::CoordinatorClient::requestFinished, this,
                      reply));
}

void CoordinatorClient::setPlayingAdvertisement(bool f_enabled)
{
    if (f_enabled) {
        playing->start();
    }
    else {
        playing->stop();
    }
}

void CoordinatorClient::requestFinished(QNetworkReply *f_reply)
{
    QString endpoint = f_reply->url().fileName();
    if (f_reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error received from endpoint " << endpoint
                 << ". Error Code:" << f_reply->error();
        f_reply->deleteLater();
        return;
    }
    QByteArray reply_raw = f_reply->readAll();

    if (reply_raw.isEmpty()) {
        qDebug() << "Invalid reply. Coordinator reply is empty.";
        f_reply->deleteLater();
        return;
    }

    switch (QVariant(endpoint.toUpper()).value<DocumentType>()) {
    case DocumentType::MOTD:
        qDebug() << "Got valid response from" << f_reply->url();
        emit motdReceived(reply_raw);
        break;

    case DocumentType::PRIVACY:
        qDebug() << "Got valid response from" << f_reply->url();
        emit privacyNoticeReceived(reply_raw);
        break;

    case DocumentType::VERSION:
        qDebug() << "Got valid response from" << f_reply->url();
        emit latestVersionReceived(reply_raw);
        break;

    case DocumentType::SERVERS:

        QJsonParseError error;
        QJsonDocument serverlist = QJsonDocument::fromJson(reply_raw, &error);
        if (error.error != QJsonParseError::NoError) {
            qCritical() << "Error parsing serverlist. Error" << error.errorString();
            break;
        }

        if (!serverlist.isArray()) {
            qDebug() << "Unable to parse serverlist. Not an array.";
            break;
        }

        QVector<ServerInfo> servers = parseServers(serverlist.array());
        qDebug() << "Got valid response from" << f_reply->url();
        emit serverlistReceived(servers);
        break;
    }
    f_reply->deleteLater();
}

void CoordinatorClient::playingTimeout()
{
    QNetworkRequest request(QUrl(BASE_URL + "playing"));
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent());
    http->post(request, QByteArray());
}

QVector<ServerInfo> CoordinatorClient::parseServers(const QJsonArray &f_servers)
{
    QVector<ServerInfo> servers = {};
    for (const auto &entry : f_servers) {
        if (!entry.isObject()) {
            qDebug() << "Unable to parse entry. Entry is not an object.";
            continue;
        }

        const QJsonObject l_entry = entry.toObject();
        ServerInfo server;
        server.name = l_entry["name"].toString();
        server.description = l_entry["description"].toString();
        server.ip = l_entry["ip"].toString();
        server.players = l_entry["players"].toInt();
        server.ws_port = l_entry["ws_port"].toInt(-1);
        server.wss_port = l_entry["wss_port"].toInt(-1);
        servers.append(server);
    }
    return servers;
}
