#include "notificationpacket.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString NotificationPacket::header() const
{
    return "INFORMATION";
}

bool NotificationPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isArray()) {
        qDebug() << "Unable to parse NotificationPacket. Body is not array.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonArray l_data = value.toArray();
    for (const QVariant &l_notification : l_data.toVariantList()) {
        notifications.append(l_notification.toString());
    }
    return true;
}

QByteArray NotificationPacket::toJson() const
{
    QJsonObject l_data;
    id = QRandomGenerator64::global()->generate64();
    l_data["id"] = QString::number(id);
    l_data["header"] = header();
    l_data["data"] = QJsonArray::fromStringList(notifications);

    return QJsonDocument(l_data).toJson(QJsonDocument::Compact);
}
