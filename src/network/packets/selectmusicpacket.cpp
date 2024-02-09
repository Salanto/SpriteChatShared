#include "selectmusicpacket.h"

SelectMusicPacket::SelectMusicPacket()
{
}

QString SelectMusicPacket::header() const
{
    return "SELECT_MUSIC";
}

bool SelectMusicPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray SelectMusicPacket::toJson() const
{
    return QByteArray();
}

int SelectMusicPacket::channel() const
{
    return music_channel;
}

void SelectMusicPacket::setChannel(const int &f_channel)
{
    music_channel = f_channel;
}

QString SelectMusicPacket::song() const
{
    return song_name;
}

void SelectMusicPacket::setSong(const QString &f_song)
{
    song_name = f_song;
}

MusicTypes::MusicFlags SelectMusicPacket::flags() const
{
    return behaviour_flags;
}

void SelectMusicPacket::setFlags(const MusicTypes::MusicFlags &f_flags)
{
    behaviour_flags = f_flags;
}
