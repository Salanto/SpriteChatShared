#ifndef SELECTMUSICPACKET_H
#define SELECTMUSICPACKET_H

#include "abstractpacket.h"
#include "musictypes.h"

class SPRITECHATSHARED_EXPORT SelectMusicPacket : public AbstractPacket
{
  public:
    SelectMusicPacket() = default;

    virtual QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

    int channel() const;
    void setChannel(const int &f_channel);

    QString song() const;
    void setSong(const QString &f_song);

    MusicTypes::MusicFlags flags() const;
    void setFlags(const MusicTypes::MusicFlags &f_flags);

  protected:
    int music_channel;
    QString song_name;
    MusicTypes::MusicFlags behaviour_flags;
};

#endif // SELECTMUSICPACKET_H
