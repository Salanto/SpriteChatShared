#include "packetrouter.h"

#include <QDebug>

void PacketRouter::registerListener(QString f_identifier, QString f_listener, Route f_route)
{
    qDebug() << "Adding listener" << f_listener << "for packet" << f_identifier;
    Routes l_routes = routes[f_identifier];
    l_routes.insert(f_listener, f_route);
    routes[f_identifier] = l_routes;
}

void PacketRouter::removeListener(QString f_identifier, QString f_listener)
{
    qDebug() << "Removing listener" << f_listener << "for packet" << f_identifier;
    Routes l_routes = routes[f_identifier];
    l_routes.remove(f_listener);
    routes[f_identifier] = l_routes;
}

void PacketRouter::route(std::shared_ptr<AbstractPacket> f_packet)
{
    if (!canRoute(f_packet->header())) {
        qDebug() << "Unable to route packet with header" << f_packet->header();
        return;
    }

    Routes l_routes = routes[f_packet->header()];
    for (Route route : qAsConst(l_routes)) {
        std::invoke(route, f_packet);
    };
}

bool PacketRouter::canRoute(QString f_route)
{
    return routes.count(f_route);
}
