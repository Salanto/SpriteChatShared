#ifndef SIDELISTPACKET_H
#define SIDELISTPACKET_H

#include "abstractpacket.h"
#include "areatypes.h"

class SPRITECHATSHARED_EXPORT SidelistPacket : public AbstractPacket
{
  public:
    SidelistPacket() = default;

    virtual QString header() const;
    virtual bool fromJsonValue(const QJsonValue &value);
    virtual QByteArray toJson() const;

    QList<AreaTypes::SideEntry> sides() const;
    void setSides(const QList<AreaTypes::SideEntry> &f_sides);

  protected:
    QList<AreaTypes::SideEntry> side_entries;
};

#endif // SIDELISTPACKET_H
