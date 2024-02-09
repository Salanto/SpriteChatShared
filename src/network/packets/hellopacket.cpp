#include "hellopacket.h"

HelloPacket::HelloPacket()
{
}

QString HelloPacket::header() const
{
    return "HELLO";
}

bool HelloPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray HelloPacket::toJson() const
{
    return QByteArray();
}

void HelloPacket::setApplicationName(const QString &f_app_name)
{
    application_name = f_app_name;
}

QString HelloPacket::applicationName() const
{
    return application_name;
}

void HelloPacket::setVersion(const QVersionNumber &f_version)
{
    application_version = f_version;
}

QVersionNumber HelloPacket::version() const
{
    return application_version;
}

void HelloPacket::setIdentifier(const QString &f_identifier)
{
    client_identifier = f_identifier;
}

QString HelloPacket::identifier() const
{
    return client_identifier;
}
