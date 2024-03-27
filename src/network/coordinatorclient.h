#ifndef COORDINATORCLIENT_H
#define COORDINATORCLIENT_H

#include <QObject>

#include "coordinatortypes.h"

class QNetworkAccessManager;
class QNetworkReply;
class QTimer;

class SPRITECHATSHARED_EXPORT CoordinatorClient : public QObject
{
    Q_OBJECT

  public:
    explicit CoordinatorClient(QObject *parent = nullptr, const QString &f_user_agent = "UNKNOWN", bool playing_advertisement = false);

    QString userAgent() const;

    void requestAll();
    void requestDocument(CoordinatorTypes::DocumentType f_type);

  signals:
    void serverlistReceived(QVector<CoordinatorTypes::ServerInfo> serverlist);
    void motdReceived(QString motd);
    void privacyNoticeReceived(QString privacy);
    void latestVersionReceived(QString version);

  public slots:
    void setPlayingAdvertisement(bool f_enabled);

  private slots:
    void requestFinished(QNetworkReply *f_reply);
    void playingTimeout();

  private:
    QVector<CoordinatorTypes::ServerInfo> parseServers(const QJsonArray &f_servers);

    const QString user_agent;
    const QString BASE_URL = "https://servers.aceattorneyonline.com/";
    const int PLAYER_HEARTBEAT_TIMEOUT = 1000 * 60 * 5;
    QNetworkAccessManager *http;
    QTimer *playing;
};

#endif // COORDINATORCLIENT_H
