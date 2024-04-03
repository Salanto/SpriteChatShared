#include "serversocket.h"

#include <QSysInfo>

const int NO_CERTIFICATE = 0;
const int NO_PORT = -1;

ServerSocket::ServerSocket(CoordinatorTypes::ServerInfo f_server, QString f_endpoint, QObject *parent) :
    QObject{parent},
    server{f_server},
    endpoint{f_endpoint}
{
    socket = new QWebSocket(QSysInfo::machineHostName(), QWebSocketProtocol::VersionLatest, this);
    connect(socket, &QWebSocket::disconnected, this, &ServerSocket::disconnectedFromHost);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &ServerSocket::dataReady);
    connect(socket, &QWebSocket::connected, this, &ServerSocket::connected);
    connect(socket, &QWebSocket::errorOccurred, this, &ServerSocket::socketErrorOccured);
}

void ServerSocket::connectToEndpoint(ServerSocket::SocketMode f_mode)
{
    QString connection_uri;
    mode = f_mode;
    if (mode == ServerSocket::SECURE) {
        qDebug() << "Selected secure connection.";
        connection_uri = QString("wss://%1:%2/%3").arg(server.ip, QString::number(server.wss_port), endpoint);
        connect(socket, &QWebSocket::sslErrors, this, &ServerSocket::handleSslError);
        QSslConfiguration ssl_config = socket->sslConfiguration();
        if (ssl_config.caCertificates().size() == NO_CERTIFICATE) {
            qWarning() << "Unable to load CA Certificates.";
            return emit errorOccured("Unable to load CA Certificates.");
        }
    }
    else {
        qDebug() << "Selected insecure connection.";
        connection_uri = QString("ws://%1:%2/%3").arg(server.ip, QString::number(server.ws_port), endpoint);
    }
    qDebug() << "Connecting to" << connection_uri;
    socket->open(connection_uri);
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

void ServerSocket::write(const QByteArray &message)
{
    socket->sendBinaryMessage(message);
}

void ServerSocket::socketErrorOccured(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error" << error;
    emit errorOccured(socket->errorString());
}

void ServerSocket::handleSslError(const QList<QSslError> errors)
{
    for (const QSslError &error : errors) {
        qWarning() << "Ssl error occured:" << error.errorString();
        emit errorOccured(error.errorString());
    }
}

void ServerSocket::disconnectedFromHost()
{
    if (mode == ServerSocket::SECURE) {
        if (server.ws_port != NO_PORT) {
            qDebug() << "Downgrading connection to insecure.";
            connectToEndpoint(ServerSocket::INSECURE);
            return;
        }
        qDebug() << "Unable to downgrade connection. Insecure port not available.";
    }
    emit connectionLost();
}
