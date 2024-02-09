#include "characterpacket.h"

CharacterPacket::CharacterPacket()
{
}

QString CharacterPacket::header() const
{
    return "CHARACTER";
}
