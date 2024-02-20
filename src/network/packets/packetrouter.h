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
    void backgroundReceived(std::shared_ptr<AbstractPacket> f_packet);
    void characterReceived(std::shared_ptr<AbstractPacket> f_packet);
    void charlistReceived(std::shared_ptr<AbstractPacket> f_packet);
    void charlistTakenReceived(std::shared_ptr<AbstractPacket> f_packet);
    void chatMessageReceived(std::shared_ptr<AbstractPacket> f_packet);
    void locationListReceived(std::shared_ptr<AbstractPacket> f_packet);
    void musicReceived(std::shared_ptr<AbstractPacket> f_packet);
    void notificationReceived(std::shared_ptr<AbstractPacket> f_packet);
    void metaDataReceived(std::shared_ptr<AbstractPacket> f_packet);
    void sideReceived(std::shared_ptr<AbstractPacket> f_packet);
    void sideListReceived(std::shared_ptr<AbstractPacket> f_packet);
    void viewportAnimationReceived(std::shared_ptr<AbstractPacket> f_packet);

  private:
    std::map<QString, Route> routes;
};

#endif // PACKETROUTER_H
