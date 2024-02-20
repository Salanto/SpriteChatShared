#ifndef CHATPACKET_H
#define CHATPACKET_H

#include "abstractpacket.h"
#include "areatypes.h"

class SPRITECHATSHARED_EXPORT ChatPacket : public AbstractPacket
{
  public:
    ChatPacket() = default;

    QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

    QString message() const;
    void setMessage(const QString &f_message);

    QString sender() const;
    void setSender(const QString &f_sender);

    AreaTypes::RGB color() const;
    void setColor(const AreaTypes::RGB &f_colour);

  protected:
    QString ooc_message;
    QString message_sender;
    AreaTypes::RGB sender_color;
};

#endif // CHATPACKET_H
