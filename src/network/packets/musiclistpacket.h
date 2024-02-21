#ifndef MUSICLISTPACKET_H
#define MUSICLISTPACKET_H

#include "abstractpacket.h"
#include "musictypes.h"
#include "spritechatshared_global.h"

class MusiclistPacket : public AbstractPacket
{
  public:
    MusiclistPacket() = default;

    QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

  private:
    MusicTypes::MusicList musiclist;
};

#endif // MUSICLISTPACKET_H
