#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include "spritechatshared_global.h"

#include <QJsonValue>
#include <QRandomGenerator64>
#include <QString>

class SPRITECHATSHARED_EXPORT AbstractPacket
{
  public:
    virtual ~AbstractPacket(){};

    virtual QString header() const = 0;
    virtual bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) = 0;
    virtual QByteArray toJson() const = 0;

    uint64_t getID() { return id; }

  protected:
    mutable uint64_t id;
};

#endif // ABSTRACTPACKET_H
