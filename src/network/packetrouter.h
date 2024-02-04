#ifndef PACKETROUTER_H
#define PACKETROUTER_H

#include "abstractpacket.h"

#include <QString>
#include <map>

class PacketRouter
{
    using Route = std::function<void(AbstractPacket *)>;
    using Routes = QList<Route>;

  public:
    PacketRouter() = default;

    void registerRoute(QString f_identifier, Route f_route);
    void route(AbstractPacket *f_packet);

  private:
    bool canRoute(QString f_route);
    std::map<QString, Routes> routes;
};

#endif // PACKETROUTER_H
