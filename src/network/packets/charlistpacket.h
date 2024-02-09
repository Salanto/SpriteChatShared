#ifndef CHARLISTPACKET_H
#define CHARLISTPACKET_H

#include "abstractpacket.h"

class SPRITECHATSHARED_EXPORT CharlistPacket : public AbstractPacket
{
  public:
    CharlistPacket();

    virtual QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    void setCharacters(const QStringList &f_characters);
    QStringList characters() const;

  private:
    QStringList charlist;
};

#endif // CHARLISTPACKET_H
