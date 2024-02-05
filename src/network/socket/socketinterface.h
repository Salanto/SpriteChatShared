#ifndef SOCKETINTERFACE_H
#define SOCKETINTERFACE_H

#include "sockettypes.h"
#include "spritechatshared_global.h"

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QtWebSockets/QWebSocket>

class SPRITECHATSHARED_EXPORT SocketInterface : public QObject
{
    Q_OBJECT

  public:
    explicit SocketInterface(QObject *parent = nullptr);
    ~SocketInterface() = default;

    virtual void connect(QString hostname, int port, QString endpoint,
                         SocketTypes::SocketMode mode = SocketTypes::INSECURE) = 0;
    virtual void close();
    virtual void close(QWebSocketProtocol::CloseCode f_code);
    virtual void write(QByteArray data);

  protected:
    QWebSocket *socket = nullptr;

  signals:
    void dataReceived(const QByteArray &message);
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError);
};

#endif // SOCKETINTERFACE_H
