#ifndef CHATPACKET_H
#define CHATPACKET_H

#include "abstractpacket.h"
#include "areatypes.h"

class SPRITECHATSHARED_EXPORT ChatPacket : public AbstractPacket
{
  public:
    ChatPacket();

    QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    QString message() const;
    void setMessage(const QString &f_message);

    QString sender() const;
    void setSender(const QString &f_sender);

    AreaTypes::RGB colour() const;
    void setColour(const AreaTypes::RGB &f_colour);

  private:
    QString ooc_message;
    QString message_sender;
    AreaTypes::RGB sender_colour;
};

#endif // CHATPACKET_H
