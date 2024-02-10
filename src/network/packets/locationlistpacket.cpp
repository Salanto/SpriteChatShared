#include "locationlistpacket.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString LocationListPacket::header() const
{
    return "LOCATIONLIST";
}

bool LocationListPacket::fromJsonValue(const QJsonValue &value)
{
    if (!value.isArray()) {
        qDebug() << "Unable to parse LocationListPacket. Body is not array.";
        return false;
    }

    // Lord have mercy.
    const QJsonArray l_array = value.toArray();

    for (const QJsonValue &l_location_value : l_array) {
        if (!l_location_value.isObject()) {
            qDebug() << "Unable to parse location. Data is not object.";
            continue;
        }

        AreaTypes::LocationMetadata l_metadata;
        QJsonObject l_location = l_location_value.toObject();
        l_metadata.id = l_location["id"].toInt(-1);
        l_metadata.playercount = l_location["playercount"].toInt();
        l_metadata.event = l_location["event"].toString();
        l_metadata.rgb_color = AreaTypes::RGB().fromString(l_location["color"].toString());
        l_metadata.background = l_location["background"].toString();
        l_metadata.description = l_location["description"].toString();
        locations_data.insert(l_metadata.id, l_metadata);
    }
    return true;
}

QByteArray LocationListPacket::toJson() const
{
    QJsonArray l_data;

    for (const AreaTypes::LocationMetadata &l_metadata : locations()) {
        QJsonObject l_location;
        l_location["id"] = l_metadata.id;
        l_location["playercount"] = l_metadata.playercount;
        l_location["event"] = l_metadata.event;
        l_location["color"] = l_metadata.rgb_color.toString();
        l_location["background"] = l_metadata.background;
        l_location["description"] = l_metadata.description;
        l_data.append(l_location);
    }

    QJsonObject l_body;
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

QVector<AreaTypes::LocationMetadata> LocationListPacket::locations() const
{
    return locations_data;
}

void LocationListPacket::setLocations(const QVector<AreaTypes::LocationMetadata> &f_locations)
{
    locations_data = f_locations;
}
