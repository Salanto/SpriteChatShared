#include "serverrouter.h"
#include "abstractpacket.h"
#include "packetfactory.h"
#include "serversocket.h"

#include <QAbstractSocket>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <QWebSocketProtocol>
#include <memory>

#define GAMEROUTE "GAME"
#define DATAROUTE "DATA"
#define DEFAULT_TIMEOUT 1000 * 10 // 10 Seconds is plenty of time.

ServerRouter::ServerRouter(QObject *parent) :
    QObject{parent}
{
    // Loading screen bullshit.
    QObject::connect(this, &ServerRouter::t_loadingLocations, &::ServerRouter::loadingLocations);
    QObject::connect(this, &ServerRouter::t_loadingMusic, &ServerRouter::loadingMusic);
    QObject::connect(this, &ServerRouter::t_loadingCharacters, &ServerRouter::loadingCharacters);

    routes["BACKGROUND"] = &ServerRouter::backgroundReceived;
    routes["SELECTCHARACTER"] = &ServerRouter::characterReceived;
    routes["CHARLIST"] = &ServerRouter::t_loadingCharacters;
    routes["CHARLISTTAKEN"] = &ServerRouter::charlistTakenReceived;
    routes["CHAT"] = &ServerRouter::chatMessageReceived;
    routes["LOCATIONLIST"] = &ServerRouter::t_loadingLocations;
    routes["MUSIC"] = &ServerRouter::musicReceived;
    routes["MUSICLIST"] = &ServerRouter::t_loadingMusic;
    routes["NOTIFICATION"] = &ServerRouter::notificationReceived;
    routes["SERVERHELLO"] = &ServerRouter::metaDataReceived;
    routes["SIDE"] = &ServerRouter::sideReceived;
    routes["SIDELIST"] = &ServerRouter::sideListReceived;
    routes["VIEWPORT"] = &ServerRouter::viewportAnimationReceived;

    metadata_timeout = new QTimer(this);
    metadata_timeout->setInterval(DEFAULT_TIMEOUT);
}

void ServerRouter::connectToDataEndpoint(CoordinatorTypes::ServerInfo f_server)
{
    QObject::connect(socket, &ServerSocket::connected, this, [this] {
        QObject::connect(metadata_timeout, &QTimer::timeout, this, [this] {
            emit errorOccured("Server did not respond in time with metadata.");
        });
        QObject::connect(this, &ServerRouter::metaDataReceived, this, [this](std::shared_ptr<AbstractPacket> f_packet) {
            Q_UNUSED(f_packet);
            metadata_timeout->stop();
            emit connectedToData();
        });
        metadata_timeout->start();
    });
    connect(f_server, DATAROUTE);
}

void ServerRouter::connectToGameEndpoint(CoordinatorTypes::ServerInfo f_server)
{
    connect(f_server, GAMEROUTE);
}

void ServerRouter::connect(CoordinatorTypes::ServerInfo f_server, QString endpoint)
{
    deleteSocket();
    socket = new ServerSocket(f_server, endpoint, this);
    QObject::connect(socket, &ServerSocket::errorOccured, this, &ServerRouter::errorOccured);
    QObject::connect(socket, &ServerSocket::dataReady, this, &ServerRouter::receive);
    QObject::connect(socket, &ServerSocket::connectionLost, this, &ServerRouter::socketDisconnected);
    ServerSocket::SocketMode l_mode = f_server.wss_port != -1 ? ServerSocket::SECURE : ServerSocket::INSECURE;
    socket->connectToEndpoint(l_mode);
}

void ServerRouter::disconnect(QWebSocketProtocol::CloseCode f_code, QString f_reason)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnect(f_code, f_reason);
    }
    else {
        socket->disconnect();
    }
}

void ServerRouter::write(const QByteArray &f_data)
{
    socket->write(f_data);
}

void ServerRouter::receive(const QByteArray &f_data)
{
    QJsonParseError error;
    QJsonDocument l_json_message = QJsonDocument::fromJson(f_data, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing message " << error.errorString();
        socket->disconnect(QWebSocketProtocol::CloseCodeProtocolError, "Invalid JSON received.");
        return;
    }

    if (!l_json_message.isObject()) {
        qDebug() << "Error parsing message. Message is not an object.";
        socket->disconnect(QWebSocketProtocol::CloseCodeProtocolError, "Message is not an object.");
        return;
    }

    QJsonObject obj = l_json_message.object();
    if (!obj["header"].isString()) {
        qDebug() << "Error parsing message. Header missing or invalid.";
        socket->disconnect(QWebSocketProtocol::CloseCodeProtocolError, "Missing or invalid header.");
        return;
    }

    QString l_header = obj["header"].toString();
    if (!canRoute(l_header)) {
        qDebug() << "Unable to route packet with header" << l_header;
        return;
    }

    QJsonValue l_data = obj["data"];
    QJsonValue l_id = obj["id"];
    std::shared_ptr<AbstractPacket> l_packet = PacketFactory::createPacket(l_header, l_id, l_data);
    if (l_packet.get() == nullptr) {
        qDebug() << "Constructed packet is not valid or no constructor is available.";
        return;
    }

    route(l_packet);
}

void ServerRouter::socketDisconnected()
{
    routes["CHARLIST"] = &ServerRouter::t_loadingCharacters;
    routes["MUSICLIST"] = &ServerRouter::t_loadingMusic;
    routes["LOCATIONLIST"] = &ServerRouter::t_loadingLocations;
}

void ServerRouter::loadingLocations(std::shared_ptr<AbstractPacket> f_packet)
{
    routes["LOCATIONLIST"] = &ServerRouter::locationListReceived;
    emit loadingStep(LoadingTypes::POPULATE_AREAS);
    emit locationListReceived(f_packet);
}

void ServerRouter::loadingMusic(std::shared_ptr<AbstractPacket> f_packet)
{
    routes["MUSICLIST"] = &ServerRouter::musiclistReceived;
    emit loadingStep(LoadingTypes::POPULATE_MUSIC);
    emit musiclistReceived(f_packet);
}

void ServerRouter::loadingCharacters(std::shared_ptr<AbstractPacket> f_packet)
{
    routes["CHARLIST"] = &ServerRouter::charlistReceived;
    emit loadingStep(LoadingTypes::POPULATE_CHARACTERS);
    emit musiclistReceived(f_packet);
}

void ServerRouter::deleteSocket()
{
    if (socket) {
        QObject::disconnect(socket, &ServerSocket::errorOccured, this, &ServerRouter::errorOccured);
        QObject::disconnect(socket, &ServerSocket::dataReady, this, &ServerRouter::receive);
        QObject::disconnect(socket, &ServerSocket::connectionLost, this, &ServerRouter::socketDisconnected);
        socket->deleteLater();
    }
}

bool ServerRouter::canRoute(QString f_header)
{
    return routes.contains(f_header);
}

void ServerRouter::route(std::shared_ptr<AbstractPacket> f_packet)
{
    if (!canRoute(f_packet.get()->header())) {
        qDebug() << "Unable to route packet. Header unknown.";
        return;
    }
    qDebug() << "Routing packet with header" << f_packet.get()->header();
    Route route = routes[f_packet->header()];
    emit(this->*route)(f_packet);
}
