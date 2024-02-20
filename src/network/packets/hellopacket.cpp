#include "hellopacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString HelloPacket::header() const
{
    return "HELLO";
}

bool HelloPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse HelloPacket. Body is not object.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonObject l_data = value.toObject();
    application_name = l_data["application"].toString("UNKNOWN");
    application_version = QVersionNumber::fromString(l_data["version"].toString("0.0.0"));
    client_identifier = l_data["identifier"].toString("INVALID");
    return true;
}

QByteArray HelloPacket::toJson() const
{
    QJsonObject l_data;
    l_data["application"] = application_name;
    l_data["version"] = application_version.toString();
    l_data["identifier"] = client_identifier;

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
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
