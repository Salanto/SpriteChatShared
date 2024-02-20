#include "packetfactory.h"
#include "abstractpacket.h"
#include "notificationpacket.h"
#include "serverhellopacket.h"

#include <QtAssert>

bool PacketFactory::canCreatePacket(const QString &f_header)
{
    return builders.count(f_header);
}

std::shared_ptr<AbstractPacket> PacketFactory::createPacket(const QString &f_header, const QJsonValue &f_id, const QJsonValue &f_data)
{
    if (!canCreatePacket(f_header)) {
        return std::shared_ptr<AbstractPacket>(nullptr);
    }
    return std::invoke(builders[f_header], f_id, f_data);
}

void PacketFactory::registerPackets()
{
    registerPacket<NotificationPacket>();
    registerPacket<ServerHelloPacket>();
}

template <class T>
void PacketFactory::registerPacket()
{
    QString l_header = T().header();
    Q_ASSERT(!builders.contains(l_header));
    builders[l_header] = &createInstance<T>;
}

template <class T>
std::shared_ptr<AbstractPacket> PacketFactory::createInstance(const QJsonValue &f_id, const QJsonValue &f_data)
{
    std::shared_ptr<T> l_packet = std::make_shared<T>();
    if (l_packet.get()->fromJsonValue(f_id, f_data)) {
        return l_packet;
    }
    return std::shared_ptr<AbstractPacket>(nullptr);
}
