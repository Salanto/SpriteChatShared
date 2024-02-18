#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include "coordinatortypes.h"
#include "sockettypes.h"
#include "spritechatshared_global.h"

#include <QObject>

class ServerSocket;
class PacketRouter;

class SPRITECHATSHARED_EXPORT ServerClient : public QObject
{
    Q_OBJECT

  public:
    explicit ServerClient(QObject *parent = nullptr);
    ~ServerClient();

    void setRouter(PacketRouter *f_router);
    void freeSocket();
    void freeRouter();

  signals:
    void disconnected(QString reason);

  public slots:
    void fetchServerMetadata(const CoordinatorTypes::ServerInfo &f_server);
    void joinServer(const CoordinatorTypes::ServerInfo &f_server);
    void disconnectSocket();

  private slots:
    void handleServerMessage(const QByteArray &f_message);

  private:
    void setSocket(ServerSocket *f_socket);
    void connectToServer(const CoordinatorTypes::ServerInfo &f_server, const QString &f_endpoint, const SocketTypes::SocketMode &f_mode);
    const QString DATAROUTE = "data";
    const QString GAMEROUTE = "game";
    ServerSocket *socket = nullptr;
    PacketRouter *router = nullptr;
};

#endif // SERVERCLIENT_H
