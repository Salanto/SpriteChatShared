#ifndef SELECTLOCATIONPACKET_H
#define SELECTLOCATIONPACKET_H

#include "abstractpacket.h"

class SPRITECHATSHARED_EXPORT SelectLocationPacket : public AbstractPacket
{
  public:
    SelectLocationPacket();

    QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    int area() const;
    void setArea(const int &f_area);

    int location() const;
    void setLocation(const int &f_location);

  private:
    int area_index;
    int location_index;
};

#endif // SELECTLOCATIONPACKET_H
