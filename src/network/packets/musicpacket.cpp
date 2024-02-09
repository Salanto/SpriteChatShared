#include "musicpacket.h"

MusicPacket::MusicPacket()
{
}

QString MusicPacket::header() const
{
    return "MUSIC";
}

bool MusicPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray MusicPacket::toJson() const
{
    return QByteArray();
}

QString MusicPacket::character() const
{
    return player_character;
}

void MusicPacket::setCharacter(const QString &f_character)
{
    player_character = f_character;
}

QString MusicPacket::name() const
{
    return displayname;
}

void MusicPacket::setName(const QString &f_name)
{
    displayname = f_name;
}
