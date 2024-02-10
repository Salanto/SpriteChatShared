#include "viewportpacket.h"

QString ViewportPacket::header() const
{
    return "VIEWPORT";
}

bool ViewportPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray ViewportPacket::toJson() const
{
    return QByteArray();
}

QString ViewportPacket::displayName() const
{
    return displayname;
}

void ViewportPacket::setDisplayName(const QString &f_displayname)
{
    displayname = f_displayname;
}

QString ViewportPacket::side() const
{
    return character_side;
}

void ViewportPacket::setSide(const QString &f_side)
{
    character_side = f_side;
}

QList<AbstractAnimationEvent *> ViewportPacket::events() const
{
    return ic_events;
}

void ViewportPacket::setEvents(const QList<AbstractAnimationEvent *> &f_events)
{
    ic_events = f_events;
}
