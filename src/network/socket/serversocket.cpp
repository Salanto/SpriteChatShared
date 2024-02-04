#include "serversocket.h"

#include <QSysInfo>

ServerSocket::ServerSocket(QObject *parent) :
    SocketInterface{parent}
{
    ws_socket = new QWebSocket(QSysInfo::machineHostName(), QWebSocketProtocol::VersionLatest, this);
    QObject::connect(ws_socket, &QWebSocket::connected, this,
                     &ServerSocket::connected);
    QObject::connect(ws_socket, &QWebSocket::disconnected, this,
                     &ServerSocket::disconnected);
    QObject::connect(ws_socket, &QWebSocket::binaryMessageReceived, this,
                     &ServerSocket::dataReceived);
    QObject::connect(ws_socket, &QWebSocket::errorOccurred, this,
                     &ServerSocket::error);
}

void ServerSocket::connect(QString hostname, int port, QString endpoint,
                           SocketTypes::SocketMode mode)
{
    QUrl server_url;
    if (mode == SocketTypes::SocketMode::SECURE) {
        QObject::connect(ws_socket, &QWebSocket::sslErrors, this,
                         &ServerSocket::handleSslError);
        QSslConfiguration ssl_config = ws_socket->sslConfiguration();
        if (ssl_config.caCertificates().size() == NO_CERTIFICATE) {
            qDebug() << "Unable to obtain SSL certificates. Certstore is empty.";
            // TODO : Try to load CA bundle from QRC for plattforms that may have
            // issues. (iOS & Android + Random Linux Distros.)
        }
        ssl_config.setProtocol(QSsl::TlsV1_2OrLater);
        ws_socket->setSslConfiguration(ssl_config);
        server_url = QUrl(QString("wss://%1:%2/%3")
                              .arg(hostname, QString::number(port), endpoint));
    }
    else {
        server_url = QUrl(QString("ws://%1:%2/%3")
                              .arg(hostname, QString::number(port), endpoint));
    }
    qDebug() << "Trying to connect to " << server_url;
    qDebug() << "Secure :" << mode;

    ws_socket->open(server_url);
}

void ServerSocket::handleSslError(const QList<QSslError> errors)
{
    for (const QSslError &error : errors) {
        qDebug() << "Encountered SSL error during connection: "
                 << error.errorString();
    }
    ws_socket->close(QWebSocketProtocol::CloseCodeTlsHandshakeFailed);
}
