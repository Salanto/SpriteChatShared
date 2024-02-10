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

    QString name() const;
    void setName(const QString &f_name);

  protected:
    QString displayname;
};

#endif // MUSICPACKET_H
