#include "serverhellopacket.h"

ServerHelloPacket::ServerHelloPacket()
{
}

QString ServerHelloPacket::header() const
{
    return "SERVER_HELLO";
}

bool ServerHelloPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray ServerHelloPacket::toJson() const
{
    return QByteArray();
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

void ServerHelloPacket::setPackages(const QList<int> &f_packages)
{
    suggested_packages = f_packages;
}

QList<int> ServerHelloPacket::packages() const
{
    return suggested_packages;
}
