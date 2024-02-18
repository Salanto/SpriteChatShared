#include "packetrouter.h"

#include <QDebug>

PacketRouter::PacketRouter(QObject *parent) :
    QObject(parent)
{
    routes["SERVERHELLO"] = &PacketRouter::metaDataReceived;
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
