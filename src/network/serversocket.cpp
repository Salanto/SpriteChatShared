#include "serversocket.h"

#include <QSysInfo>

ServerSocket::ServerSocket(CoordinatorTypes::ServerInfo f_server, QString f_endpoint, QObject *parent) :
    QWebSocket{QSysInfo::machineHostName(), QWebSocketProtocol::VersionLatest, parent},
    server{f_server},
    endpoint{f_endpoint}
{
    qDebug() << "Create socket for host" << server.ip << "endpoint" << endpoint;
}

void ServerSocket::connectToEndpoint(SocketTypes::SocketMode mode)
{
    if (mode == SocketTypes::SECURE) {
        connect(this, &QWebSocket::sslErrors, this, &ServerSocket::handleSslError);
        QSslConfiguration ssl_config = sslConfiguration();
        if (ssl_config.caCertificates().size() == NO_CERTIFICATE) {
            qWarning() << "Unable to load CA Certificates.";
            emit sslErrorOccurred();
            return;
        }
    }
}

void ServerSocket::handleSslError(const QList<QSslError> errors)
{
    for (const QSslError &error : errors) {
        qWarning() << "Ssl error occured:" << error.errorString();
    }
    emit sslErrorOccurred();
    connectToEndpoint(SocketTypes::SocketMode::INSECURE);
}
