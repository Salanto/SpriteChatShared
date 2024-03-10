#include "mount.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

Mount::Mount(QString path) :
    m_path(path)
{}

Mount::~Mount()
{
    resetReader();
}

QString Mount::path()
{
    return m_path;
}

bool Mount::load()
{
    resetReader();

    try {
        m_reader = new bit7z::BitArchiveReader(m_library, m_path.toStdString(), bit7z::BitFormat::Zip);
        m_reader->test();
    } catch (const std::exception &e) {
        errorOccurred(MountError::FailedToLoadMount, QString("Failed to load %1").arg(m_path));
        return false;
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
        } catch (const std::exception &e) {
            errorOccurred(MountError::FailedToIndexMount, QString("Failed to index %1").arg(m_path));
            return false;
        }
        saveCache();
    }

    return true;
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
    } catch (const std::exception &e) {
        errorOccurred(MountError::FailedToFetchFile, QString("Failed to fetch %1 in %2").arg(path, m_path));
        return QByteArray();
    }

    return QByteArray(reinterpret_cast<const char *>(buffer.data()), buffer.size());
}

bool Mount::loadCache()
{
    QFile file(m_path + ".cache");
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDataStream stream(&file);
    QDateTime cache_last_modified;
    stream >> cache_last_modified;
    if (cache_last_modified < m_last_modified) {
        return false;
    }

    m_cache.clear();
    stream >> m_cache;
    if (stream.status() != QDataStream::Ok) {
        errorOccurred(MountError::FailedToLoadCache, QString("Failed to load cache %1").arg(m_path));
        return false;
    }

    return true;
}

void Mount::saveCache()
{
    QFile file(m_path + ".cache");
    if (!file.open(QIODevice::WriteOnly)) {
        errorOccurred(MountError::FailedToSaveCache, QString("Failed to save cache %1 of %2").arg(m_path, file.errorString()));
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
        errorOccurred(MountError::FailedToResetMount, QString("Failed to reset mount %1").arg(m_path));
        qCritical() << e.what();
    }
}
