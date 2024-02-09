#include "setsidepacket.h"

SetSidePacket::SetSidePacket()
{
}

QString SetSidePacket::header() const
{
    return "SETSIDE";
}

bool SetSidePacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray SetSidePacket::toJson() const
{
    return QByteArray();
}

QString SetSidePacket::side() const
{
    return requested_side;
}

void SetSidePacket::setSide(const QString &f_side)
{
    requested_side = f_side;
}
