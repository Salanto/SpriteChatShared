#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include <QJsonObject>
#include <QString>

class AbstractPacket
{
  public:
    virtual ~AbstractPacket(){};

    virtual QString header() const = 0;
    virtual bool fromJsonValue(const QJsonValue &value) = 0;
    virtual QByteArray toJson() const = 0;
};

#endif // ABSTRACTPACKET_H
