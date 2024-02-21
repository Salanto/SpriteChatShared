#include "packetfactory.h"
#include "abstractpacket.h"
#include "backgroundpacket.h"
#include "characterpacket.h"
#include "charlistpacket.h"
#include "charlisttakenpacket.h"
#include "chatpacket.h"
#include "hellopacket.h"
#include "locationlistpacket.h"
#include "locationpacket.h"
#include "musiclistpacket.h"
#include "musicpacket.h"
#include "notificationpacket.h"
#include "selectmusicpacket.h"
#include "serverhellopacket.h"
#include "setsidepacket.h"
#include "sidelistpacket.h"
#include "viewportpacket.h"

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
    registerPacket<BackgroundPacket>();
    registerPacket<CharacterPacket>();
    registerPacket<CharlistPacket>();
    registerPacket<CharlistTakenPacket>();
    registerPacket<ChatPacket>();
    registerPacket<HelloPacket>();
    registerPacket<LocationListPacket>();
    registerPacket<LocationPacket>();
    registerPacket<MusiclistPacket>();
    registerPacket<MusicPacket>();
    registerPacket<NotificationPacket>();
    registerPacket<SelectMusicPacket>();
    registerPacket<ServerHelloPacket>();
    registerPacket<SetSidePacket>();
    registerPacket<SidelistPacket>();
    registerPacket<ViewportPacket>();
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
