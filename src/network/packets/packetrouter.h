#ifndef PACKETROUTER_H
#define PACKETROUTER_H

#include "abstractpacket.h"
#include "spritechatshared_global.h"

#include <QString>
#include <map>

class SPRITECHATSHARED_EXPORT PacketRouter
{
    using Route = std::function<void(std::shared_ptr<AbstractPacket>)>;
    using Routes = QMap<QString, Route>;

  public:
    PacketRouter() = default;

    void registerListener(QString f_identifier, QString f_listener, Route f_route);
    void removeListener(QString f_identifier, QString f_listener);
    void route(std::shared_ptr<AbstractPacket> f_packet);
    bool canRoute(QString f_route);

  private:
    std::map<QString, Routes> routes;
};

#endif // PACKETROUTER_H
