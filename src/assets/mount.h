#pragma once

#include "spritechatshared_global.h"

#include "include/bit7z/bit7zlibrary.hpp"
#include "include/bit7z/bitarchivereader.hpp"

#include <QDateTime>
#include <QMap>
#include <QObject>

class SPRITECHATSHARED_EXPORT Mount : public QObject
{
    Q_OBJECT

  public:
    Mount(QString path);
    ~Mount();

    QString path();

    bool load();

    bool containsFile(QString path);

    /**
     * @warning The file fetched MUST exist.
     */
    QByteArray fetchFile(QString path);

  Q_SIGNALS:
    void errorOccurred(MountError error, QString message);

  private:
    bool loadCache();
    void saveCache();

    void resetReader();

    QString m_path;
    QDateTime m_last_modified;
    QMap<QString, uint32_t> m_cache;
    const bit7z::Bit7zLibrary m_library;
    bit7z::BitArchiveReader *m_reader = nullptr;
};
