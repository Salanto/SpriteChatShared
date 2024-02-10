#ifndef CHARACTERPACKET_H
#define CHARACTERPACKET_H

#include "abstractpacket.h"

class SPRITECHATSHARED_EXPORT CharacterPacket : public AbstractPacket
{
  public:
    CharacterPacket() = default;

    virtual QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    QString character() const;
    void setCharacter(const QString &f_character);

  protected:
    QString selected_character;
};

#endif // CHARACTERPACKET_H
