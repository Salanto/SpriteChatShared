#include "characterpacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString CharacterPacket::header() const
{
    return "SELECTCHARACTER";
}

bool CharacterPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse CharacterPacket. Body is not object.";
        return false;
    }

    QJsonObject l_data = value.toObject();
    selected_character = l_data["character"].toString();
    id = f_id.toString().toULongLong();
    return true;
}

QByteArray CharacterPacket::toJson() const
{
    QJsonObject l_data;
    l_data["character"] = selected_character;

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

QString CharacterPacket::character() const
{
    return selected_character;
}

void CharacterPacket::setCharacter(const QString &f_character)
{
    selected_character = f_character;
}
