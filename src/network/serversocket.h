#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "coordinatortypes.h"
#include "sockettypes.h"
#include "spritechatshared_global.h"

#include <QByteArray>
#include <QString>
#include <QtWebSockets/QWebSocket>

class SPRITECHATSHARED_EXPORT ServerSocket : public QWebSocket
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ServerSocket)

  public:
    ServerSocket(CoordinatorTypes::ServerInfo f_server, QString f_endpoint, QObject *parent = nullptr);
    ~ServerSocket() = default;

    void connectToEndpoint(SocketTypes::SocketMode mode);

  signals:
    void sslErrorOccurred();

  private slots:
    void handleSslError(const QList<QSslError> errors);

  private:
    const CoordinatorTypes::ServerInfo server;
    const QString endpoint;
    const int NO_CERTIFICATE = 0;
};

#endif // SERVERSOCKET_H
