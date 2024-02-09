#include "charlistpacket.h"

CharlistPacket::CharlistPacket()
{
}

QString CharlistPacket::header() const
{
    return "CHARLIST";
}

bool CharlistPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray CharlistPacket::toJson() const
{
    return QByteArray();
}

void CharlistPacket::setCharacters(const QStringList &f_characters)
{
    charlist = f_characters;
}

QStringList CharlistPacket::characters() const
{
    return charlist;
}
