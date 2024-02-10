#include "musicpacket.h"

#include <QJsonDocument>
#include <QJsonObject>

MusicPacket::MusicPacket() :
    SelectMusicPacket()
{
}

QString MusicPacket::header() const
{
    return "MUSIC";
}

bool MusicPacket::fromJsonValue(const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse MusicPacket. Body is not object.";
        return false;
    }

    QJsonObject l_data = value.toObject();
    displayname = l_data["displayname"].toString();
    music_channel = l_data["channel"].toInt(0);
    song_name = l_data["songname"].toString();
    behaviour_flags = l_data["flags"].toVariant().value<MusicTypes::MusicFlags>();

    return true;
}

QByteArray MusicPacket::toJson() const
{
    QJsonObject l_data;
    l_data["displayname"] = displayname;
    l_data["channel"] = music_channel;
    l_data["songname"] = song_name;
    l_data["flags"] = behaviour_flags.toInt();

    QJsonObject l_body;
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

QString MusicPacket::name() const
{
    return displayname;
}

void MusicPacket::setName(const QString &f_name)
{
    displayname = f_name;
}
