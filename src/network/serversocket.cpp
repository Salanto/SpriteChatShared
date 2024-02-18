#include "serversocket.h"

#include <QSysInfo>

ServerSocket::ServerSocket(CoordinatorTypes::ServerInfo f_server, QString f_endpoint, QObject *parent) :
    QObject{parent},
    server{f_server},
    endpoint{f_endpoint}
{
    socket = new QWebSocket(QSysInfo::machineHostName(), QWebSocketProtocol::VersionLatest, this);
    qDebug() << "Create socket for host" << server.ip << "endpoint" << endpoint;
    connect(socket, &QWebSocket::disconnected, this, &ServerSocket::disconnectedFromHost);
}

void ServerSocket::connectToEndpoint(SocketTypes::SocketMode f_mode)
{
    QString connection_uri;
    mode = f_mode;
    if (mode == SocketTypes::SECURE) {
        connection_uri = QString("wss://%1:%2/%3").arg(server.ip, QString::number(server.wss_port), endpoint);
        connect(socket, &QWebSocket::sslErrors, this, &ServerSocket::handleSslError);
        QSslConfiguration ssl_config = socket->sslConfiguration();
        if (ssl_config.caCertificates().size() == NO_CERTIFICATE) {
            qWarning() << "Unable to load CA Certificates.";
            emit sslErrorOccurred();
            return;
        }
    }
}

void ServerSocket::disconnect(QWebSocketProtocol::CloseCode f_reason, const QString &f_message)
{
    blockSignals(true);
    socket->close(f_reason, f_message);
}

QAbstractSocket::SocketState ServerSocket::state()
{
    return socket->state();
}

void ServerSocket::handleSslError(const QList<QSslError> errors)
{
    for (const QSslError &error : errors) {
        qWarning() << "Ssl error occured:" << error.errorString();
    }
    emit sslErrorOccurred();
}

void ServerSocket::disconnectedFromHost()
{
    if (mode == SocketTypes::SECURE) {
        if (server.ws_port != NO_PORT) {
            connectToEndpoint(SocketTypes::INSECURE);
            return;
        }
    }
    emit connectionLost();
}
