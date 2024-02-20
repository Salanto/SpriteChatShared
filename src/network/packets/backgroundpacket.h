#ifndef BACKGROUNDPACKET_H
#define BACKGROUNDPACKET_H

#include "abstractpacket.h"

class SPRITECHATSHARED_EXPORT BackgroundPacket : public AbstractPacket
{
  public:
    BackgroundPacket() = default;

    QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

    QString background() const;
    void setBackground(const QString &f_background);

    bool reset() const;
    void setReset(const bool &f_bool);

  protected:
    QString background_name = "default";
    bool reset_background = false;
};

#endif // BACKGROUNDPACKET_H
