#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "sockettypes.h"
#include "spritechatshared_global.h"

#include <QByteArray>
#include <QString>
#include <QtWebSockets/QWebSocket>

class SPRITECHATSHARED_EXPORT ServerSocket : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ServerSocket)

  public:
    ServerSocket(QObject *parent = nullptr);
    ~ServerSocket() = default;

    void connect(QString hostname, int port, QString endpoint,
                 SocketTypes::SocketMode mode = SocketTypes::INSECURE);
    virtual void close(QWebSocketProtocol::CloseCode f_code = QWebSocketProtocol::CloseCodeNormal);
    virtual void write(QByteArray data);
    QAbstractSocket::SocketState state();

  signals:
    void dataReceived(const QByteArray &message);
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError);
    void sslError();

  private slots:
    void handleSslError(const QList<QSslError> error);

  private:
    const int NO_CERTIFICATE = 0;
    QWebSocket *socket = nullptr;
};

#endif // SERVERSOCKET_H
