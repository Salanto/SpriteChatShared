#include "packetrouter.h"

void PacketRouter::route(AbstractPacket *f_packet)
{
    Routes l_routes = routes[f_packet->header()];
    for (Route route : l_routes) {
        std::invoke(route, f_packet);
    };
}

bool PacketRouter::canRoute(QString f_route)
{
    return routes.count(f_route);
}
