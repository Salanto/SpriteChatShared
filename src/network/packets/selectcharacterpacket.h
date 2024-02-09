#ifndef SELECTCHARACTERPACKET_H
#define SELECTCHARACTERPACKET_H

#include "abstractpacket.h"

class SPRITECHATSHARED_EXPORT SelectCharacterPacket : public AbstractPacket
{
  public:
    SelectCharacterPacket();

    virtual QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    QString character() const;
    void setCharacter(const QString &f_character);

  private:
    QString selected_character;
};

#endif // SELECTCHARACTERPACKET_H
