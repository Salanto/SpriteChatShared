#include "mount.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

Mount::Mount(AssetTypes::MountData info, QObject *parent) :
    QObject{parent},
    information{info}
{
    if (!QFile::exists(information.path) || !open()) {
        return;
    }

    QFileInfo l_mount_file_info(information.path);
    if (l_mount_file_info.lastModified() != information.last_modified) {
        mount_state = AssetTypes::MODIFIED;
        information.last_modified = l_mount_file_info.lastModified();
    }
    else {
        mount_state = AssetTypes::UNMODIFIED;
    }
    loadCache();
}

Mount::~Mount()
{
    saveCache();
}

bool Mount::open()
{
    handle = new bit7z::BitArchiveReader(context, information.path.toStdString(),
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

AssetTypes::MountState Mount::state()
{
    return mount_state;
}

QString Mount::path()
{
    return information.path;
}

void Mount::loadCache()
{
    if (state() == AssetTypes::MODIFIED) {
        QFile::remove(cachePath());
    }

    if (!QFile::exists(cachePath())) {
        auto items = handle->items();
        for (const bit7z::BitArchiveItemInfo &item : items) {
            QString path = QString::fromStdString(item.path()).replace("\\", "/");
            cached_paths.insert(path, item.index());
        }
        return;
    }

    QFile cache(cachePath());
    if (cache.open(QIODevice::ReadOnly)) {
        QDataStream in(&cache);
        in >> cached_paths;
        cache.close();
    }
}

void Mount::saveCache()
{
    QFile cache(cachePath());
    if (cache.open(QIODevice::WriteOnly)) {
        QDataStream out(&cache);
        out << cached_paths;
        cache.close();
    }
    else {
        qDebug() << cache.errorString();
    }
}

QString Mount::cachePath() const
{
    QStringList cache_path_split = information.path.split("/");
    cache_path_split.removeLast();
    return cache_path_split.join("/").append(".path");
}
