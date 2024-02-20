#ifndef LOCATIONPACKET_H
#define LOCATIONPACKET_H

#include "abstractpacket.h"

class SPRITECHATSHARED_EXPORT LocationPacket : public AbstractPacket
{
  public:
    LocationPacket() = default;

    QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

    int area() const;
    void setArea(const int &f_area);

    int location() const;
    void setLocation(const int &f_location);

  protected:
    int area_index;
    int location_index;
};

#endif // LOCATIONPACKET_H
