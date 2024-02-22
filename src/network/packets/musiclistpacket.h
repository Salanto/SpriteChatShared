#ifndef MUSICLISTPACKET_H
#define MUSICLISTPACKET_H

#include "abstractpacket.h"
#include "musictypes.h"
#include "spritechatshared_global.h"

class SPRITECHATSHARED_EXPORT MusiclistPacket : public AbstractPacket
{
  public:
    MusiclistPacket() = default;

    QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

    MusicTypes::MusicList musiclist() const;
    void setMusiclist(const MusicTypes::MusicList &f_musiclist);

  private:
    MusicTypes::MusicList m_musiclist;
};

#endif // MUSICLISTPACKET_H
