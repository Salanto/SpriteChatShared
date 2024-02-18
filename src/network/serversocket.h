#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "coordinatortypes.h"
#include "sockettypes.h"
#include "spritechatshared_global.h"

#include <QByteArray>
#include <QString>
#include <QWebSocketProtocol>
#include <QtWebSockets/QWebSocket>

class SPRITECHATSHARED_EXPORT ServerSocket : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ServerSocket)

  public:
    ServerSocket(CoordinatorTypes::ServerInfo f_server, QString f_endpoint, QObject *parent = nullptr);
    ~ServerSocket() = default;

    void connectToEndpoint(SocketTypes::SocketMode f_mode);
    void disconnect(QWebSocketProtocol::CloseCode f_reason = QWebSocketProtocol::CloseCodeNormal, const QString &f_message = "");
    QAbstractSocket::SocketState state();

  signals:
    void sslErrorOccurred();
    void connectionLost();
    void dataReady(const QByteArray &f_message);

  private slots:
    void handleSslError(const QList<QSslError> errors);
    void disconnectedFromHost();

  private:
    const CoordinatorTypes::ServerInfo server;
    const QString endpoint;
    const int NO_CERTIFICATE = 0;
    const int NO_PORT = -1;
    SocketTypes::SocketMode mode;
    QWebSocket *socket;
};

#endif // SERVERSOCKET_H
