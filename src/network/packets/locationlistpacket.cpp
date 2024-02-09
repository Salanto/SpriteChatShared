#include "locationlistpacket.h"

QString LocationListPacket::header() const
{
    return "LOCATIONLIST";
}

bool LocationListPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray LocationListPacket::toJson() const
{
    return QByteArray();
}

AreaTypes::LocationMetadata LocationListPacket::locations() const
{
    return locations_data;
}

void LocationListPacket::setLocations(const AreaTypes::LocationMetadata &f_locations)
{
    locations_data = f_locations;
}
