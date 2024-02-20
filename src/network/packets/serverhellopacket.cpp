#include "serverhellopacket.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString ServerHelloPacket::header() const
{
    return "SERVERHELLO";
}

bool ServerHelloPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse ServerHelloPacket. Body is not object.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonObject l_data = value.toObject();
    server_app = l_data["application"].toString("UNKNOWN");
    server_version = QVersionNumber::fromString(l_data["version"].toString("0.0.0"));
    server_name = l_data["name"].toString("UNKNOWN");
    server_description = l_data["description"].toString("UNKNOWN");
    server_playercount = l_data["playercount"].toInt(0);
    asset_url = l_data["url"].toString();

    QJsonValue l_package_array = l_data["packages"];
    if (!l_package_array.isArray()) {
        qDebug() << "Unable to parse packages. Packages are not array.";
        return false;
    }

    QJsonArray l_packages = l_package_array.toArray();
    for (const QVariant &l_package : l_packages.toVariantList()) {
        suggested_packages.append(l_package.toString());
    }
    return true;
}

QByteArray ServerHelloPacket::toJson() const
{
    QJsonObject l_data;
    l_data["application"] = server_app;
    l_data["version"] = server_version.toString();
    l_data["name"] = server_name;
    l_data["description"] = server_description;
    l_data["playercount"] = server_playercount;
    l_data["url"] = asset_url;
    l_data["packages"] = QJsonArray::fromStringList(suggested_packages);

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

void ServerHelloPacket::setAppName(const QString &f_app_name)
{
    server_app = f_app_name;
}

QString ServerHelloPacket::appName() const
{
    return server_app;
}

void ServerHelloPacket::setVersion(const QVersionNumber &f_version)
{
    server_version = f_version;
}

QVersionNumber ServerHelloPacket::version() const
{
    return server_version;
}

void ServerHelloPacket::setName(const QString &f_name)
{
    server_name = f_name;
}

QString ServerHelloPacket::name() const
{
    return server_name;
}

void ServerHelloPacket::setDescription(const QString &f_description)
{
    server_description = f_description;
}

QString ServerHelloPacket::description() const
{
    return server_description;
}

void ServerHelloPacket::setPlayercount(const int &f_playercount)
{
    server_playercount = f_playercount;
}

int ServerHelloPacket::playercount() const
{
    return server_playercount;
}

void ServerHelloPacket::setAssetUrl(const QString &f_asset_url)
{
    asset_url = f_asset_url;
}

QString ServerHelloPacket::assetUrl() const
{
    return asset_url;
}

void ServerHelloPacket::setPackages(const QStringList &f_packages)
{
    suggested_packages = f_packages;
}

QStringList ServerHelloPacket::packages() const
{
    return suggested_packages;
}
