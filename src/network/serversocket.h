#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "coordinatortypes.h"
#include "qabstractsocket.h"
#include "spritechatshared_global.h"
#include <QByteArray>
#include <QQueue>
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

    enum SocketMode : bool
    {
        INSECURE = false,
        SECURE = true
    };
    Q_ENUM(SocketMode);

    void connectToEndpoint(ServerSocket::SocketMode f_mode);
    void disconnect(QWebSocketProtocol::CloseCode f_reason = QWebSocketProtocol::CloseCodeNormal, const QString &f_message = "");
    QAbstractSocket::SocketState state();
    void write(const QByteArray &message);

  signals:
    void errorOccured(QString error_message);
    void connectionLost();
    void connected();
    void dataReady(const QByteArray &f_message);

  private slots:
    void socketErrorOccured(QAbstractSocket::SocketError error);
    void handleSslError(const QList<QSslError> errors);
    void disconnectedFromHost();

  private:
    const CoordinatorTypes::ServerInfo server;
    const QString endpoint;
    ServerSocket::SocketMode mode;
    QQueue<QByteArray> buffer;
    QWebSocket *socket;
};

#endif // SERVERSOCKET_H
