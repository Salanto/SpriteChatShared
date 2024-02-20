#ifndef LOCATIONLISTPACKET_H
#define LOCATIONLISTPACKET_H

#include "abstractpacket.h"
#include "areatypes.h"

class SPRITECHATSHARED_EXPORT LocationListPacket : public AbstractPacket
{
  public:
    LocationListPacket() = default;

    virtual QString header() const;
    virtual bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value);
    virtual QByteArray toJson() const;

    QVector<AreaTypes::LocationMetadata> locations() const;
    void setLocations(const QVector<AreaTypes::LocationMetadata> &f_locations);

  protected:
    QVector<AreaTypes::LocationMetadata> locations_data;
};

#endif // LOCATIONLISTPACKET_H
