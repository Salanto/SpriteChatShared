#include "sidelistpacket.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString SidelistPacket::header() const
{
    return "SIDELIST";
}

bool SidelistPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isArray()) {
        qDebug() << "Unable to parse SideListPacket. Body is not array.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonArray l_sides = value.toArray();
    for (const QJsonValue &l_side : l_sides) {
        if (!l_side.isObject()) {
            qDebug() << "Unable to parse side. Entry is not object.";
            continue;
        }
        QJsonObject side = l_side.toObject();
        AreaTypes::SideEntry entry;
        entry.side = side["side"].toString("witness");
        entry.image = side["image"].toString("witness.png");
        entry.overlay = side["overlay"].toString("overlay.png");
    }
    return true;
}

QByteArray SidelistPacket::toJson() const
{
    QJsonArray l_data;
    for (const AreaTypes::SideEntry &entry : sides()) {
        QJsonObject l_entry;
        l_entry["side"] = entry.side;
        l_entry["image"] = entry.image;
        l_entry["overlay"] = entry.overlay;
        l_data.append(l_entry);
    }

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

QList<AreaTypes::SideEntry> SidelistPacket::sides() const
{
    return side_entries;
}

void SidelistPacket::setSides(const QList<AreaTypes::SideEntry> &f_sides)
{
    side_entries = f_sides;
}
