#include "backgroundpacket.h"

BackgroundPacket::BackgroundPacket()
{
}

QString BackgroundPacket::header() const
{
    return "BACKGROUND";
}

bool BackgroundPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray BackgroundPacket::toJson() const
{
    return QByteArray();
}

QString BackgroundPacket::background() const
{
    return background_name;
}

void BackgroundPacket::setBackground(const QString &f_background)
{
    background_name = f_background;
}

bool BackgroundPacket::reset() const
{
    return reset_background;
}

void BackgroundPacket::setReset(const bool &f_bool)
{
    reset_background = f_bool;
}
