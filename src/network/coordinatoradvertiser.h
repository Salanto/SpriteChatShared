#ifndef COORDINATORADVERTISER_H
#define COORDINATORADVERTISER_H

#include "coordinatortypes.h"
#include "spritechatshared_global.h"

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QTimer;

class SPRITECHATSHARED_EXPORT CoordinatorAdvertiser : public QObject
{
    Q_OBJECT

  public:
    explicit CoordinatorAdvertiser(QObject *parent = nullptr, const QString &f_user_agent = "UNKNOWN");

    QString userAgent() const;

    void setEnabled(bool f_enabled);
    CoordinatorTypes::ServerInfo *metaDataRW();

  private slots:
    void advertise();
    void finished(QNetworkReply *f_reply);

  private:
    const int HEARTBEAT = 1000 * 60 * 5;
    const QString user_agent;
    const QString BASE_URL = "https://servers.aceattorneyonline.com/";
    QNetworkAccessManager *http;
    QTimer *timeout;
    CoordinatorTypes::ServerInfo serverinfo;
};

#endif // COORDINATORADVERTISER_H
