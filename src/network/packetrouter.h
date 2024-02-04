#ifndef PACKETROUTER_H
#define PACKETROUTER_H

#include "abstractpacket.h"

#include <functional>
#include <map>
#include <string>

class PacketRouter
{
  public:
    PacketRouter();

    // Callbacks or signals?
    // using Route = void (HVACRouter::*)(QJsonObject);
    // std::map<QString, Route> routes;

    // std::map<std::string, std::function<void(AbstractPacket *)>> routes;
    // std::map<QString,
};

#endif // PACKETROUTER_H
