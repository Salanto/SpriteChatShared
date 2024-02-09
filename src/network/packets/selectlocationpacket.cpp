#include "selectlocationpacket.h"

SelectLocationPacket::SelectLocationPacket()
{
}

QString SelectLocationPacket::header() const
{
    return "SELECT_LOCATION";
}

bool SelectLocationPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray SelectLocationPacket::toJson() const
{
    return QByteArray();
}

int SelectLocationPacket::area() const
{
    return area_index;
}

void SelectLocationPacket::setArea(const int &f_area)
{
    area_index = f_area;
}

int SelectLocationPacket::location() const
{
    return location_index;
}

void SelectLocationPacket::setLocation(const int &f_location)
{
    location_index = f_location;
}
