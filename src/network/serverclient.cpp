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
    prouter = new PacketRouter(this);
}

ServerClient::~ServerClient()
{
    freeSocket();
    freeRouter();
}

PacketRouter *ServerClient::router()
{
    return prouter;
}

void ServerClient::setSocket(ServerSocket *f_socket)
{
    freeSocket();
    ssocket = f_socket;
    connect(ssocket, &ServerSocket::dataReady, this, &ServerClient::handleServerMessage);
}

void ServerClient::freeSocket()
{
    if (ssocket) {
        disconnect(ssocket, &ServerSocket::dataReady, this, &ServerClient::handleServerMessage);
        ssocket->disconnect();
        ssocket->deleteLater();
        ssocket = nullptr;
    }
}

void ServerClient::freeRouter()
{
    if (prouter) {
        delete prouter;
    }
}

void ServerClient::handleServerMessage(const QByteArray &f_message)
{
    QJsonParseError error;
    QJsonDocument l_json_message = QJsonDocument::fromJson(f_message, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing message " << error.errorString();
        ssocket->disconnect(QWebSocketProtocol::CloseCodeProtocolError, "Invalid JSON received.");
        return;
    }

    if (!l_json_message.isObject()) {
        qDebug() << "Error parsing message. Message is not an object.";
        ssocket->disconnect(QWebSocketProtocol::CloseCodeProtocolError, "Message is not an object.");
        return;
    }

    QJsonObject obj = l_json_message.object();
    if (!obj["header"].isString()) {
        qDebug() << "Error parsing message. Header missing or invalid.";
        ssocket->disconnect(QWebSocketProtocol::CloseCodeProtocolError, "Missing or invalid header.");
        return;
    }

    QString l_header = obj["header"].toString();
    if (!prouter->canRoute(l_header)) {
        qDebug() << "Unable to route packet with header" << l_header;
        return;
    }

    QJsonValue l_data = obj["data"];
    std::shared_ptr<AbstractPacket> l_packet = PacketFactory::createPacket(l_header, l_data);
    if (l_packet.get() == nullptr) {
        qDebug() << "Constructed packet is not valid or no constructor is available.";
        return;
    }

    prouter->route(l_packet);
}

void ServerClient::disconnectSocket()
{
    if (ssocket) {
        if (ssocket->state() != QAbstractSocket::UnconnectedState) {
            ssocket->disconnect();
        }
    }
}

void ServerClient::fetchServerMetadata(const CoordinatorTypes::ServerInfo &f_server)
{
    if (f_server.wss_port != -1) {
        connectToServer(f_server, DATAROUTE, SocketTypes::SECURE);
    }
    else {
        connectToServer(f_server, DATAROUTE, SocketTypes::INSECURE);
    }
}

void ServerClient::joinServer(const CoordinatorTypes::ServerInfo &f_server)
{
    if (f_server.wss_port != -1) {
        connectToServer(f_server, GAMEROUTE, SocketTypes::SECURE);
    }
    else {
        connectToServer(f_server, GAMEROUTE, SocketTypes::INSECURE);
    }
}

void ServerClient::connectToServer(const CoordinatorTypes::ServerInfo &f_server, const QString &f_endpoint,
                                   const SocketTypes::SocketMode &f_mode)
{
    setSocket(new ServerSocket(f_server, f_endpoint, this));
    ssocket->connectToEndpoint(f_mode);
}
