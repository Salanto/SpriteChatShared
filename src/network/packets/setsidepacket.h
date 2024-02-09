#ifndef SETSIDEPACKET_H
#define SETSIDEPACKET_H

#include "abstractpacket.h"

class SetSidePacket : public AbstractPacket
{
  public:
    SetSidePacket();

    virtual QString header() const;
    virtual bool fromJsonValue(const QJsonValue &value);
    virtual QByteArray toJson() const;

    QString side() const;
    void setSide(const QString &f_side);

  private:
    QString requested_side;
};

#endif // SETSIDEPACKET_H
