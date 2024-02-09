#include "sidelistpacket.h"

SidelistPacket::SidelistPacket()
{
}

QString SidelistPacket::header() const
{
    return "SIDELIST";
}

bool SidelistPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray SidelistPacket::toJson() const
{
    return QByteArray();
}

QList<AreaTypes::SideEntry> SidelistPacket::sides()
{
    return side_entries;
}

void SidelistPacket::setSides(const QList<AreaTypes::SideEntry> &f_sides)
{
    side_entries = f_sides;
}
