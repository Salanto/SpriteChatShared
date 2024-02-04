#include "packetfactory.h"

#include "assert.h"

bool PacketFactory::canCreatePacket(std::string f_header)
{
    return builders.count(f_header);
}

AbstractPacket *PacketFactory::createPacket(QByteArray f_data)
{
}

void PacketFactory::registerPackets()
{
}

template <typename T>
void PacketFactory::registerPacket(std::string header)
{
    T packet;
    assert()
}

template <typename T>
AbstractPacket *PacketFactory::createInstance(QJsonValue f_data)
{
}
