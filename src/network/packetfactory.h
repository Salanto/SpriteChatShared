#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include "abstractpacket.h"

#include <QString>

class PacketFactory
{
  public:
    PacketFactory() = delete;
    ~PacketFactory() = delete;

    static bool canCreatePacket(QString f_header);
    static std::shared_ptr<AbstractPacket> createPacket(QByteArray f_data);

    template <class T, is_packet<T> = true>
    static void registerPacket();
    static void registerPackets();

  private:
    template <class T, is_packet<T> = true>
    static std::shared_ptr<AbstractPacket> createInstance(QJsonValue f_data);
    inline static std::map<QString, AbstractPacket *(*)(QJsonValue)> builders;
};

#endif // PACKETFACTORY_H
