#include "packetrouter.h"

#include <QDebug>

void PacketRouter::registerRoute(QString f_identifier, Route f_route)
{
    Routes l_routes = routes[f_identifier];
    l_routes.append(f_route);
    routes[f_identifier] = l_routes;
}

void PacketRouter::route(std::shared_ptr<AbstractPacket> f_packet)
{
    if (!canRoute(f_packet->header())) {
        qDebug() << "Unable to route packet with header" << f_packet->header();
        return;
    }

    Routes l_routes = routes[f_packet->header()];
    for (Route route : l_routes) {
        std::invoke(route, f_packet);
    };
}

bool PacketRouter::canRoute(QString f_route)
{
    return routes.count(f_route);
}
