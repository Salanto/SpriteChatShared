#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include "spritechatshared_global.h"

#include <QObject>

class ServerSocket;
class PacketRouter;

class SPRITECHATSHARED_EXPORT ServerClient : public QObject
{
    Q_OBJECT

  public:
    explicit ServerClient(QObject *parent = nullptr);

    void setSocket(ServerSocket *f_socket);
    void setRouter(PacketRouter *f_router);
    void freeSocket();

  private slots:
    void handleServerMessage(const QByteArray &f_message);

  private:
    ServerSocket *socket = nullptr;
    PacketRouter *router = nullptr;
};

#endif // SERVERCLIENT_H
