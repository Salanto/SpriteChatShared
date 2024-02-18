#ifndef PACKETROUTER_H
#define PACKETROUTER_H

#include "abstractpacket.h"
#include "spritechatshared_global.h"

#include <QObject>
#include <QString>
#include <map>

class SPRITECHATSHARED_EXPORT PacketRouter : public QObject
{
    Q_OBJECT
    using Route = void (PacketRouter::*)(std::shared_ptr<AbstractPacket>);

  public:
    PacketRouter(QObject *parent = nullptr);
    void route(std::shared_ptr<AbstractPacket> f_packet);
    bool canRoute(QString f_route);

  signals:
    void metaDataReceived(std::shared_ptr<AbstractPacket> f_packet);

  private:
    std::map<QString, Route> routes;
};

#endif // PACKETROUTER_H
