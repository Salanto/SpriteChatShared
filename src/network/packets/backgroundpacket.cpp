#include "backgroundpacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString BackgroundPacket::header() const
{
    return "BACKGROUND";
}

bool BackgroundPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse BackgroundPacket. Body is not object.";
        return false;
    }

    QJsonObject l_data = value.toObject();
    background_name = l_data["name"].toString("default");
    reset_background = l_data["reset"].toBool(false);
    id = f_id.toString().toULongLong();

    return true;
}

QByteArray BackgroundPacket::toJson() const
{
    QJsonObject l_data;
    l_data["name"] = background_name;
    l_data["reset"] = reset_background;

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
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
