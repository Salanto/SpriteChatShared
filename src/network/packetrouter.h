#ifndef PACKETROUTER_H
#define PACKETROUTER_H

#include "abstractpacket.h"
#include "spritechatshared_global.h"

#include <QString>
#include <map>

class SPRITECHATSHARED_EXPORT PacketRouter
{
    using Route = std::function<void(std::shared_ptr<AbstractPacket>)>;
    using Routes = QList<Route>;

  public:
    PacketRouter() = default;

    void registerRoute(QString f_identifier, Route f_route);
    void route(std::shared_ptr<AbstractPacket> f_packet);

  private:
    bool canRoute(QString f_route);
    std::map<QString, Routes> routes;
};

#endif // PACKETROUTER_H
