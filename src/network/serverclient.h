#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

#include <QObject>

class ServerSocket;
class PacketRouter;

class ServerClient : public QObject
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
