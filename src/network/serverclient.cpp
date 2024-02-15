#include "serverclient.h"
#include "abstractpacket.h"
#include "packetfactory.h"
#include "packetrouter.h"
#include "serversocket.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

ServerClient::ServerClient(QObject *parent) :
    QObject{parent}
{
}

ServerClient::~ServerClient()
{
    freeSocket();
    freeRouter();
}

void ServerClient::setSocket(ServerSocket *f_socket)
{
    freeSocket();
    socket = f_socket;
    connect(socket, &ServerSocket::dataReceived, this, &ServerClient::handleServerMessage);
}

void ServerClient::setRouter(PacketRouter *f_router)
{
    freeRouter();
    router = f_router;
}

void ServerClient::freeSocket()
{
    if (socket) {
        disconnect(socket, &ServerSocket::dataReceived, this, &ServerClient::handleServerMessage);
        socket->close();
        socket->deleteLater();
        socket = nullptr;
    }
}

void ServerClient::freeRouter()
{

    if (router) {
        delete router;
        router = nullptr;
    }
}

void ServerClient::handleServerMessage(const QByteArray &f_message)
{
    QJsonParseError error;
    QJsonDocument l_json_message = QJsonDocument::fromJson(f_message, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing message " << error.errorString();
        socket->close(QWebSocketProtocol::CloseCodeProtocolError);
        return;
    }

    if (!l_json_message.isObject()) {
        qDebug() << "Error parsing message. Message is not an object.";
        socket->close(QWebSocketProtocol::CloseCodeProtocolError);
        return;
    }

    QJsonObject obj = l_json_message.object();
    if (!obj["header"].isString()) {
        qDebug() << "Error parsing message. Header missing or invalid.";
        socket->close(QWebSocketProtocol::CloseCodeProtocolError);
        return;
    }

    QString l_header = obj["header"].toString();
    if (!router->canRoute(l_header)) {
        qDebug() << "Unable to route packet with header" << l_header;
        return;
    }

    QJsonValue l_data = obj["data"];
    std::shared_ptr<AbstractPacket> l_packet = PacketFactory::createPacket(l_header, l_data);
    if (l_packet.get() == nullptr) {
        qDebug() << "Constructed packet is not valid or no constructor is available.";
        return;
    }

    router->route(l_packet);
}

void ServerClient::connectToServer(const QString &hostname, const int &port, const SocketTypes::SocketMode &f_mode)
{
    setSocket(new ServerSocket(this));
    socket->connect(hostname, port, GAMEROUTE, f_mode);
}

void ServerClient::disconnectSocket()
{
    if (socket) {
        if (socket->state() != QAbstractSocket::UnconnectedState) {
            socket->close();
        }
    }
}

void ServerClient::fetchServerMetadata(const CoordinatorTypes::ServerInfo &f_server)
{
    if (f_server.wss_port != -1) {
    }
    else {
        socket->connect(f_server.)
    }
}

void ServerClient::joinServer(const CoordinatorTypes::ServerInfo &f_server)
{
}
