#include "selectmusicpacket.h"

#include <QJsonDocument>
#include <QJsonObject>

QString SelectMusicPacket::header() const
{
    return "SELECTMUSIC";
}

bool SelectMusicPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isObject()) {
        qDebug() << "Unable to parse SelectMusicPacket. Body is not object.";
        return false;
    }

    id = f_id.toString().toULongLong();
    QJsonObject l_data = value.toObject();
    music_channel = l_data["channel"].toInt(0);
    song_name = l_data["songname"].toString();
    behaviour_flags = l_data["flags"].toVariant().value<MusicTypes::MusicFlags>();
    return true;
}

QByteArray SelectMusicPacket::toJson() const
{
    QJsonObject l_data;
    l_data["channel"] = music_channel;
    l_data["songname"] = song_name;
    l_data["flags"] = behaviour_flags.toInt();

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = l_data;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}

int SelectMusicPacket::channel() const
{
    return music_channel;
}

void SelectMusicPacket::setChannel(const int &f_channel)
{
    music_channel = f_channel;
}

QString SelectMusicPacket::song() const
{
    return song_name;
}

void SelectMusicPacket::setSong(const QString &f_song)
{
    song_name = f_song;
}

MusicTypes::MusicFlags SelectMusicPacket::flags() const
{
    return behaviour_flags;
}

void SelectMusicPacket::setFlags(const MusicTypes::MusicFlags &f_flags)
{
    behaviour_flags = f_flags;
}
