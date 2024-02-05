#ifndef NOTIFICATIONPACKET_H
#define NOTIFICATIONPACKET_H

#include "abstractpacket.h"
#include "spritechatshared_global.h"

#include <QByteArray>
#include <QJsonValue>
#include <QString>
#include <QStringList>

class SPRITECHATSHARED_EXPORT NotificationPacket : public AbstractPacket
{
  public:
    NotificationPacket() = default;
    ~NotificationPacket() = default;

    QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

  private:
    QStringList messages;
};

#endif // NOTIFICATIONPACKET_H
