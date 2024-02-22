#ifndef PACKETROUTER_H
#define PACKETROUTER_H

#include "abstractpacket.h"
#include "loadingtypes.h"
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

    bool writePacket(const QByteArray packet);
  signals:
    void sendServerPacket(const QByteArray &f_packet);

    void loadingStep(LoadingTypes::LoadingState f_state);
    void t_loadingLocations(std::shared_ptr<AbstractPacket> f_packet);
    void t_loadingMusic(std::shared_ptr<AbstractPacket> f_packet);
    void t_loadingCharacters(std::shared_ptr<AbstractPacket> f_packet);

    void backgroundReceived(std::shared_ptr<AbstractPacket> f_packet);
    void characterReceived(std::shared_ptr<AbstractPacket> f_packet);
    void charlistReceived(std::shared_ptr<AbstractPacket> f_packet);
    void charlistTakenReceived(std::shared_ptr<AbstractPacket> f_packet);
    void chatMessageReceived(std::shared_ptr<AbstractPacket> f_packet);
    void locationListReceived(std::shared_ptr<AbstractPacket> f_packet);
    void musiclistReceived(std::shared_ptr<AbstractPacket> f_packet);
    void musicReceived(std::shared_ptr<AbstractPacket> f_packet);
    void notificationReceived(std::shared_ptr<AbstractPacket> f_packet);
    void metaDataReceived(std::shared_ptr<AbstractPacket> f_packet);
    void sideReceived(std::shared_ptr<AbstractPacket> f_packet);
    void sideListReceived(std::shared_ptr<AbstractPacket> f_packet);
    void viewportAnimationReceived(std::shared_ptr<AbstractPacket> f_packet);

  public slots:
    void disconnected();

  private slots:
    void loadingLocations(std::shared_ptr<AbstractPacket> f_packet);
    void loadingMusic(std::shared_ptr<AbstractPacket> f_packet);
    void loadingCharacters(std::shared_ptr<AbstractPacket> f_packet);

  private:
    std::map<QString, Route> routes;
};

#endif // PACKETROUTER_H
