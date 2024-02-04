#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "socketinterface.h"

class ServerSocket : public SocketInterface
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ServerSocket)

  public:
    ServerSocket(QObject *parent = nullptr);
    ~ServerSocket() = default;

    void connect(QString hostname, int port, QString endpoint,
                 SocketTypes::SocketMode mode = SocketTypes::INSECURE) override;

  private slots:
    void handleSslError(const QList<QSslError> error);

  private:
    const int NO_CERTIFICATE = 0;
};

#endif // SERVERSOCKET_H
