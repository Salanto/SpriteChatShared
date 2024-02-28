#include "mount.h"

#include <QDebug>
#include <QFile>

Mount::Mount(QObject *parent, QString path) :
    QObject{parent},
    phys_path{path}
{
    qDebug() << "Creating mount handle for" << path;
}

bool Mount::open()
{
    handle = new bit7z::BitArchiveReader(context, phys_path.toStdString(),
                                         bit7z::BitFormat::Auto);
    try {
        handle->test();
        return true;
    } catch (bit7z::BitException exception) {
        qDebug() << exception.what();
        return false;
    }
}

bool Mount::contains(QString file)
{
    return cached_paths.contains(file);
}

bool Mount::indexArchive(bool override)
{
    const QString cache_path = cachePath();

    if (override) {
        qDebug() << "Deleting existing cache, wether they like it or not.";
        QFile::remove(cachePath());
    }

    if (QFile::exists(cache_path)) {
        QFile cache(cache_path);
        if (cache.open(QIODevice::ReadOnly)) {
            QDataStream in(&cache);
            in >> cached_paths;
            cache.close();
            return true;
        }
    }

    auto items = handle->items();
    for (const bit7z::BitArchiveItemInfo &item : items) {
        QString path = QString::fromStdString(item.path()).replace("\\", "/");
        cached_paths.insert(path, item.index());
        qDebug() << path << item.index();
    }
    return false;
}

bool Mount::saveIndex()
{
    QFile cache(cachePath());
    if (cache.open(QIODevice::WriteOnly)) {
        QDataStream out(&cache);
        out << cached_paths;
        cache.close();
        return true;
    }
    else {
        qDebug() << cache.errorString();
    }
    return false;
}

QByteArray Mount::load(QString path)
{
    const unsigned int id = cached_paths.value(path);
    std::vector<bit7z::byte_t> buffer;

    try {
        handle->extractTo(buffer, id);
    } catch (bit7z::BitException exception) {
        qDebug() << "Caught exception:" << exception.what();
        return QByteArray();
    }
    return QByteArray(reinterpret_cast<const char *>(buffer.data()), buffer.size());
}

QString Mount::path()
{
    return phys_path;
}

QString Mount::cachePath() const
{
    QStringList cache_path_split = phys_path.split("/");
    cache_path_split.removeLast();
    return cache_path_split.join("/").append(".path");
}
