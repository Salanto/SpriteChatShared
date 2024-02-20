#include "viewportpacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString ViewportPacket::header() const
{
    return "VIEWPORT";
}

bool ViewportPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    id = f_id.toString().toULongLong();
    return false;
}

QByteArray ViewportPacket::toJson() const
{
    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
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
