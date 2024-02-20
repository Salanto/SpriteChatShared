#include "packetrouter.h"

#include <QDebug>

PacketRouter::PacketRouter(QObject *parent) :
    QObject(parent)
{
    routes["BACKGROUND"] = &PacketRouter::backgroundReceived;
    routes["SELECTCHARACTER"] = &PacketRouter::characterReceived;
    routes["CHARLIST"] = &PacketRouter::charlistReceived;
    routes["CHARLISTTAKEN"] = &PacketRouter::charlistTakenReceived;
    routes["CHAT"] = &PacketRouter::chatMessageReceived;
    routes["LOCATIONLIST"] = &PacketRouter::locationListReceived;
    routes["MUSIC"] = &PacketRouter::musicReceived;
    routes["NOTIFICATION"] = &PacketRouter::notificationReceived;
    routes["SERVERHELLO"] = &PacketRouter::metaDataReceived;
    routes["SIDE"] = &PacketRouter::sideReceived;
    routes["SIDELIST"] = &PacketRouter::sideListReceived;
    routes["VIEWPORT"] = &PacketRouter::viewportAnimationReceived;
}

void PacketRouter::route(std::shared_ptr<AbstractPacket> f_packet)
{
    if (!canRoute(f_packet.get()->header())) {
        qDebug() << "Unable to route packet. Header unknown.";
        return;
    }
    Route route = routes[f_packet->header()];
    emit(this->*route)(f_packet);
}

bool PacketRouter::canRoute(QString f_route)
{
    return routes.count(f_route);
}
