#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include "coordinatortypes.h"
#include "sockettypes.h"
#include "spritechatshared_global.h"

#include <QObject>

class ServerSocket;
class PacketRouter;
class QTimer;

class SPRITECHATSHARED_EXPORT ServerClient : public QObject
{
    Q_OBJECT

  public:
    explicit ServerClient(QObject *parent = nullptr);
    ~ServerClient();

    PacketRouter *router();

  signals:
    void disconnected(QString reason);
    void connected();
    void metadataTimeout(QString reason = "No reason provided");

  public slots:
    void fetchServerMetadata(const CoordinatorTypes::ServerInfo &f_server);
    void joinServer(const CoordinatorTypes::ServerInfo &f_server);
    void disconnectSocket();

  private slots:
    void handleServerMessage(const QByteArray &f_message);
    void writeServerMessage(const QByteArray &f_message);

  private:
    void freeSocket();
    void freeRouter();
    void setSocket(ServerSocket *f_socket);
    void connectToServer(const CoordinatorTypes::ServerInfo &f_server, const QString &f_endpoint, const SocketTypes::SocketMode &f_mode);
    const QString DATAROUTE = "data";
    const QString GAMEROUTE = "game";
    const int METADATA_TIMEOUT = 1000 * 10;
    ServerSocket *ssocket = nullptr;
    PacketRouter *prouter = nullptr;
    QTimer *timeout = nullptr;
};

#endif // SERVERCLIENT_H
