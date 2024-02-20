#include "chatpacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString ChatPacket::header() const
{
    return "CHAT";
}

bool ChatPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse ChatPacket. Body is not object.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonObject l_data = value.toObject();
    message_sender = l_data["sender"].toString();
    ooc_message = l_data["messager"].toString();
    sender_color = AreaTypes::RGB().fromString(l_data["color"].toString("255,255,255"));

    return true;
}

QByteArray ChatPacket::toJson() const
{
    QJsonObject l_data;
    l_data["sender"] = message_sender;
    l_data["message"] = ooc_message;
    l_data["color"] = sender_color.toString();

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

QString ChatPacket::message() const
{
    return ooc_message;
}

void ChatPacket::setMessage(const QString &f_message)
{
    ooc_message = f_message;
}

QString ChatPacket::sender() const
{
    return message_sender;
}

void ChatPacket::setSender(const QString &f_sender)
{
    message_sender = f_sender;
}

AreaTypes::RGB ChatPacket::color() const
{
    return sender_color;
}

void ChatPacket::setColor(const AreaTypes::RGB &f_colour)
{
    sender_color = f_colour;
}
