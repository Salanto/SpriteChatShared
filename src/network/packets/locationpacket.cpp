#include "locationpacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString LocationPacket::header() const
{
    return "LOCATION";
}

bool LocationPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse LocationPacket. Body is not object.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonObject l_data = value.toObject();
    area_index = l_data["area"].toInt(0);
    location_index = l_data["location"].toInt(0);

    return true;
}

QByteArray LocationPacket::toJson() const
{

    QJsonObject l_data;
    l_data["area"] = area_index;
    l_data["location"] = location_index;

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

int LocationPacket::area() const
{
    return area_index;
}

void LocationPacket::setArea(const int &f_area)
{
    area_index = f_area;
}

int LocationPacket::location() const
{
    return location_index;
}

void LocationPacket::setLocation(const int &f_location)
{
    location_index = f_location;
}
