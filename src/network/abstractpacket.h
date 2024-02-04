#ifndef ABSTRACTPACKET_H
#define ABSTRACTPACKET_H

#include <QJsonObject>
#include <QString>

class AbstractPacket;

template <class T>
using is_packet = std::enable_if<std::is_base_of_v<AbstractPacket, T>>;

class AbstractPacket
{
  public:
    virtual ~AbstractPacket();

    virtual QString header() const = 0;
    virtual bool fromJsonValue(const QJsonValue &value) = 0;
    virtual QByteArray toJson() const = 0;
};

#endif // ABSTRACTPACKET_H
