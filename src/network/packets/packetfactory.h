#ifndef PACKETFACTORY_H
#define PACKETFACTORY_H

#include "abstractpacket.h"
#include "spritechatshared_global.h"

#include <QString>

class SPRITECHATSHARED_EXPORT PacketFactory
{
  public:
    PacketFactory() = delete;
    ~PacketFactory() = delete;

    static bool canCreatePacket(const QString &f_header);
    static std::shared_ptr<AbstractPacket> createPacket(const QString &f_header, const QJsonValue &f_id, const QJsonValue &f_data);

    template <class T>
    static void registerPacket();
    static void registerPackets();

  protected:
    template <class T>
    static std::shared_ptr<AbstractPacket> createInstance(const QJsonValue &f_id, const QJsonValue &f_data);
    inline static std::map<QString, std::shared_ptr<AbstractPacket> (*)(const QJsonValue &, const QJsonValue &)> builders;
};

#endif // PACKETFACTORY_H
