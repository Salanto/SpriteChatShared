#include "selectcharacterpacket.h"

SelectCharacterPacket::SelectCharacterPacket()
{
}

QString SelectCharacterPacket::header() const
{
    return "SELECT_CHARACTER";
}

bool SelectCharacterPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray SelectCharacterPacket::toJson() const
{
    return QByteArray();
}

QString SelectCharacterPacket::character() const
{
    return selected_character;
}

void SelectCharacterPacket::setCharacter(const QString &f_character)
{
    selected_character = f_character;
}
