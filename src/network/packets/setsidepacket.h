#ifndef SETSIDEPACKET_H
#define SETSIDEPACKET_H

#include "abstractpacket.h"

class SetSidePacket : public AbstractPacket
{
  public:
    SetSidePacket() = default;

    virtual QString header() const;
    virtual bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value);
    virtual QByteArray toJson() const;

    QString side() const;
    void setSide(const QString &f_side);

  protected:
    QString requested_side;
};

#endif // SETSIDEPACKET_H
