#include "setsidepacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString SetSidePacket::header() const
{
    return "SETSIDE";
}

bool SetSidePacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse SetSidePacket. Body is not object";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonObject l_data = value.toObject();
    requested_side = l_data["side"].toString("witness");
    return true;
}

QByteArray SetSidePacket::toJson() const
{
    QJsonObject l_data;
    l_data["side"] = requested_side;

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

QString SetSidePacket::side() const
{
    return requested_side;
}

void SetSidePacket::setSide(const QString &f_side)
{
    requested_side = f_side;
}
