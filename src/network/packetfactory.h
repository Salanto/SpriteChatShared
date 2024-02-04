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
    static AbstractPacket *createPacket(QByteArray f_data);

    template <typename T>
    static void registerPacket(QString header);
    static void registerPackets();

  private:
    template <typename T>
    static AbstractPacket *createInstance(QJsonValue f_data);
    inline static std::map<QString, AbstractPacket *(*)(QJsonValue)> builders;
};

#endif // PACKETFACTORY_H
