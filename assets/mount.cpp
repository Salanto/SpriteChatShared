#include "mount.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

Mount::Mount(QString path) :
    m_path(path)
{
    load();
}

Mount::~Mount()
{
    resetReader();
}

QString Mount::path()
{
    return m_path;
}

void Mount::load()
{
    resetReader();

    try {
        m_reader = new bit7z::BitArchiveReader(m_library, m_path.toStdString(), bit7z::BitFormat::Auto);
        m_reader->test();
    } catch (const bit7z::BitException &e) {
        qFatal(e.what());
    }

    QFileInfo info(m_path);
    m_last_modified = info.lastModified();
    if (!loadCache()) {
        m_cache.clear();
        try {
            auto items = m_reader->items();
            for (const auto &item : items) {
                QString path = QString::fromStdString(item.path()).replace("\\", "/");
                m_cache.insert(path, item.index());
            }
        } catch (const bit7z::BitException &e) {
            qFatal(e.what());
        }
        saveCache();
    }
}

bool Mount::containsFile(QString path)
{
    return m_cache.contains(path);
}

QByteArray Mount::fetchFile(QString path)
{
    uint32_t index = m_cache.value(path);
    std::vector<bit7z::byte_t> buffer;

    try {
        m_reader->extractTo(buffer, index);
    } catch (const bit7z::BitException &e) {
        qFatal(e.what());
    }

    return QByteArray(reinterpret_cast<const char *>(buffer.data()), buffer.size());
}

bool Mount::loadCache()
{
    QFile file(m_path + ".cache");
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Failed to open file of mount" << m_path << ":" << file.errorString();
        return false;
    }

    QDataStream stream(&file);
    QDateTime cache_last_modified;
    stream >> cache_last_modified;

    if (cache_last_modified < m_last_modified) {
        qInfo() << "Skipping cache loading for mount" << m_path << ": out of date";
        return false;
    }

    m_cache.clear();
    stream >> m_cache;
    if (stream.status() != QDataStream::Ok) {
        qCritical() << "Failed to load cache of mount" << m_path << "last known status:" << stream.status();
        return false;
    }

    return true;
}

void Mount::saveCache()
{
    QFile file(m_path + ".cache");
    if (!file.open(QIODevice::WriteOnly)) {
        qCritical() << "Failed to open file of mount" << m_path << ":" << file.errorString();
        return;
    }

    QDataStream stream(&file);
    stream << m_last_modified;
    stream << m_cache;
    file.close();
}

void Mount::resetReader()
{
    try {
        if (m_reader) {
            delete m_reader;
            m_reader = nullptr;
        }
    } catch (const std::exception &e) {
        qFatal(e.what());
    }
}
