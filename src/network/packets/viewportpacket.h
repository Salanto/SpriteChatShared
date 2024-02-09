#ifndef VIEWPORTPACKET_H
#define VIEWPORTPACKET_H

#include "abstractanimationevent.h"
#include "abstractpacket.h"

class SPRITECHATSHARED_EXPORT ViewportPacket : AbstractPacket
{
  public:
    ViewportPacket();

    QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    QString displayName() const;
    void setDisplayName(const QString &f_displayname);

    QString side() const;
    void setSide(const QString &f_side);

    QList<AbstractAnimationEvent *> events() const;
    void setEvents(const QList<AbstractAnimationEvent *> &f_events);

  private:
    QString displayname;
    QString character_side;
    QList<AbstractAnimationEvent *> ic_events;
};

#endif // VIEWPORTPACKET_H
