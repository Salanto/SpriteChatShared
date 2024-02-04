#include "notificationpacket.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString NotificationPacket::header() const
{
    return "INFORMATION";
}

bool NotificationPacket::fromJsonValue(const QJsonValue &value)
{
    if (!value.isArray()) {
        return false;
    }
    return true;
}

QByteArray NotificationPacket::toJson() const
{
    QJsonObject l_data;
    l_data["header"] = header();
    l_data["data"] = QJsonArray::fromStringList(messages);

    return QJsonDocument(l_data).toJson(QJsonDocument::Compact);
}
