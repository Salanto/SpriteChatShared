#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include "abstractpacket.h"

#include <string>

class PacketFactory
{
  public:
    PacketFactory() = delete;
    ~PacketFactory() = delete;

    static bool canCreatePacket(std::string f_header);
    static AbstractPacket *createPacket(QByteArray f_data);

    template <typename T>
    static void registerPacket(std::string header);
    static void registerPackets();

  private:
    template <typename T>
    static AbstractPacket *createInstance(QJsonValue f_data);
    inline static std::map<std::string, AbstractPacket *(*)(QJsonValue)> builders;
};

#endif // PACKETFACTORY_H
