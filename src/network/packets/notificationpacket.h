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

    QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

    void setMessages(const QStringList &f_messages);
    QStringList messages() const;

  protected:
    QStringList notifications;
};

#endif // NOTIFICATIONPACKET_H
