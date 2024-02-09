#ifndef LOCATIONLISTPACKET_H
#define LOCATIONLISTPACKET_H

#include "abstractpacket.h"
#include "areatypes.h"

class SPRITECHATSHARED_EXPORT LocationListPacket : public AbstractPacket
{
  public:
    LocationListPacket();

    virtual QString header() const;
    virtual bool fromJsonValue(const QJsonValue &value);
    virtual QByteArray toJson() const;

    AreaTypes::LocationMetadata locations() const;
    void setLocations(const AreaTypes::LocationMetadata &f_locations);

  private:
    AreaTypes::LocationMetadata locations_data;
};

#endif // LOCATIONLISTPACKET_H
