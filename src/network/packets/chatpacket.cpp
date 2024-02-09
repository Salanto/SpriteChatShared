#include "chatpacket.h"

ChatPacket::ChatPacket()
{
}

QString ChatPacket::header() const
{
    return "CHAT";
}

bool ChatPacket::fromJsonValue(const QJsonValue &value)
{
    return false;
}

QByteArray ChatPacket::toJson() const
{
    return QByteArray();
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

AreaTypes::RGB ChatPacket::colour() const
{
    return sender_colour;
}

void ChatPacket::setColour(const AreaTypes::RGB &f_colour)
{
    sender_colour = f_colour;
}
