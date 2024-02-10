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
        qDebug() << "Unable to parse NotificationPacket. Body is not array.";
        return false;
    }
    QJsonArray l_data = value.toArray();
    for (const QVariant &l_notification : l_data.toVariantList()) {
        notifications.append(l_notification.toString());
    }
    return true;
}

QByteArray NotificationPacket::toJson() const
{
    QJsonObject l_data;
    l_data["header"] = header();
    l_data["data"] = QJsonArray::fromStringList(notifications);

    return QJsonDocument(l_data).toJson(QJsonDocument::Compact);
}
