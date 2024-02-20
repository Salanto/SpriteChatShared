#include "charlistpacket.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString CharlistPacket::header() const
{
    return "CHARLIST";
}

bool CharlistPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isArray()) {
        qDebug() << "Unable to parse CharlistPacket. Body is not array.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonArray l_data = value.toArray();
    for (const QVariant &l_character : l_data.toVariantList()) {
        charlist.append(l_character.toString());
    }
    return true;
}

QByteArray CharlistPacket::toJson() const
{
    QJsonArray l_data = QJsonArray::fromStringList(charlist);

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

void CharlistPacket::setCharacters(const QStringList &f_characters)
{
    charlist = f_characters;
}

QStringList CharlistPacket::characters() const
{
    return charlist;
}
