#include "musiclistpacket.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString MusiclistPacket::header() const
{
    return "MUSICLIST";
}

bool MusiclistPacket::fromJsonValue(const QJsonValue &f_id, const QJsonValue &value)
{
    if (!value.isArray()) {
        qDebug() << "Unable to parse LocationPacket. Body is not array.";
        return false;
    }

    const QJsonArray array = value.toArray();
    for (const QJsonValue &val_segment : array) {
        if (!val_segment.isObject()) {
            continue;
        }
        QJsonObject segment = val_segment.toObject();
        MusicTypes::MusicListSegment value;
        for (const QVariant &song : segment["songs"].toArray().toVariantList()) {
            value.songs.append(song.toString());
        }
        value.category = segment["category"].toString();
        musiclist.append(value);
    }
    id = f_id.toInt();
    return true;
}

QByteArray MusiclistPacket::toJson() const
{
    QJsonArray array;
    for (const MusicTypes::MusicListSegment &segment : musiclist) {
        QJsonObject l_temp;
        l_temp["category"] = segment.category;
        l_temp["songs"] = QJsonArray::fromStringList(segment.songs);
        array.append(l_temp);
    }

    QJsonObject l_body;
    id = QRandomGenerator64::global()->generate64();
    l_body["id"] = QString::number(id);
    l_body["header"] = header();
    l_body["data"] = array;
    return QJsonDocument(l_body).toJson(QJsonDocument::Compact);
}
