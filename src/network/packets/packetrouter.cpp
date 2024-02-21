#include "packetrouter.h"

#include <QDebug>

PacketRouter::PacketRouter(QObject *parent) :
    QObject(parent)
{
    connect(this, &PacketRouter::t_loadingLocations, &::PacketRouter::loadingLocations);
    connect(this, &PacketRouter::t_loadingMusic, &PacketRouter::loadingMusic);
    connect(this, &PacketRouter::t_loadingCharacters, &PacketRouter::loadingCharacters);

    routes["BACKGROUND"] = &PacketRouter::backgroundReceived;
    routes["SELECTCHARACTER"] = &PacketRouter::characterReceived;
    routes["CHARLIST"] = &PacketRouter::t_loadingCharacters;
    routes["CHARLISTTAKEN"] = &PacketRouter::charlistTakenReceived;
    routes["CHAT"] = &PacketRouter::chatMessageReceived;
    routes["LOCATIONLIST"] = &PacketRouter::t_loadingLocations;
    routes["MUSIC"] = &PacketRouter::musicReceived;
    routes["MUSICLIST"] = &PacketRouter::t_loadingMusic;
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

void PacketRouter::disconnected()
{
    routes["CHARLIST"] = &PacketRouter::t_loadingCharacters;
    routes["MUSICLIST"] = &PacketRouter::t_loadingMusic;
    routes["LOCATIONLIST"] = &PacketRouter::t_loadingLocations;
}

void PacketRouter::loadingLocations(std::shared_ptr<AbstractPacket> f_packet)
{
    routes["LOCATIONLIST"] = &PacketRouter::locationListReceived;
    emit loadingStep(LoadingTypes::POPULATE_AREAS);
    emit locationListReceived(f_packet);
}

void PacketRouter::loadingMusic(std::shared_ptr<AbstractPacket> f_packet)
{
    routes["MUSICLIST"] = &PacketRouter::musiclistReceived;
    emit loadingStep(LoadingTypes::POPULATE_MUSIC);
    emit musiclistReceived(f_packet);
}

void PacketRouter::loadingCharacters(std::shared_ptr<AbstractPacket> f_packet)
{
    routes["CHARLIST"] = &PacketRouter::charlistReceived;
    emit loadingStep(LoadingTypes::POPULATE_CHARACTERS);
    emit musiclistReceived(f_packet);
}
