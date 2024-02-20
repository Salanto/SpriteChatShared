#ifndef SERVERHELLOPACKET_H
#define SERVERHELLOPACKET_H

#include "abstractpacket.h"

#include <QString>
#include <QVersionNumber>

class SPRITECHATSHARED_EXPORT ServerHelloPacket : public AbstractPacket
{
  public:
    ServerHelloPacket() = default;

    QString header() const override;
    bool fromJsonValue(const QJsonValue &f_id, const QJsonValue &value) override;
    QByteArray toJson() const override;

    void setAppName(const QString &f_app_name);
    QString appName() const;

    void setVersion(const QVersionNumber &f_version);
    QVersionNumber version() const;

    void setName(const QString &f_name);
    QString name() const;

    void setDescription(const QString &f_description);
    QString description() const;

    void setPlayercount(const int &f_playercount);
    int playercount() const;

    void setAssetUrl(const QString &f_asset_url);
    QString assetUrl() const;

    void setPackages(const QStringList &f_packages);
    QStringList packages() const;

  protected:
    QString server_app;
    QVersionNumber server_version;
    QString server_name;
    QString server_description;
    int server_playercount;
    QString asset_url;
    QStringList suggested_packages;
};

#endif // SERVERHELLOPACKET_H
