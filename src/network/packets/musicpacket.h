#ifndef MUSICPACKET_H
#define MUSICPACKET_H

#include "selectmusicpacket.h"

class SPRITECHATSHARED_EXPORT MusicPacket : public SelectMusicPacket
{
  public:
    MusicPacket();

    QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    QString character() const;
    void setCharacter(const QString &f_character);

    QString name() const;
    void setName(const QString &f_name);

  private:
    QString player_character;
    QString displayname;
};

#endif // MUSICPACKET_H
