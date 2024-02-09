#ifndef HELLOPACKET_H
#define HELLOPACKET_H

#include "abstractpacket.h"

#include <QVersionNumber>

class SPRITECHATSHARED_EXPORT HelloPacket : public AbstractPacket
{
  public:
    HelloPacket();

    QString header() const override;
    bool fromJsonValue(const QJsonValue &value) override;
    QByteArray toJson() const override;

    void setApplicationName(const QString &f_app_name);
    QString applicationName() const;

    void setVersion(const QVersionNumber &f_version);
    QVersionNumber version() const;

    void setIdentifier(const QString &f_identifier);
    QString identifier() const;

  private:
    QString application_name;
    QVersionNumber application_version;
    QString client_identifier;
};

#endif // HELLOPACKET_H
