#include "packetfactory.h"
#include "abstractpacket.h"
#include "notificationpacket.h"

#include <QtAssert>

bool PacketFactory::canCreatePacket(QString f_header)
{
    return builders.count(f_header);
}

std::shared_ptr<AbstractPacket> PacketFactory::createPacket(QByteArray f_data)
{
    return nullptr;
}

void PacketFactory::registerPackets()
{
    registerPacket<NotificationPacket>();
}

template <class T>
void PacketFactory::registerPacket()
{
    QString l_header = T().header();
    Q_ASSERT(!builders.contains(l_header));
    builders[l_header] = &createInstance<T>;
}

template <class T>
std::shared_ptr<AbstractPacket> PacketFactory::createInstance(QJsonValue f_data)
{
    std::shared_ptr<T> l_packet = std::make_shared<T>();
    if (l_packet.get()->fromJsonValue(f_data)) {
        return l_packet;
    }
    return nullptr;
}
