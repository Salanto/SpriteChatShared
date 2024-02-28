#ifndef MOUNT_H
#define MOUNT_H

#include "bit7z/bit7zlibrary.hpp"
#include "bit7z/bitarchivereader.hpp"
#include <QHash>
#include <QObject>

class Mount : public QObject
{
    Q_OBJECT

  public:
    explicit Mount(QObject *parent = nullptr, QString path = "");

    bool open();
    bool contains(QString file);
    bool saveIndex();

    // True : We found a cache file. False : We had to index ourselves.
    bool indexArchive(bool override = false);
    QByteArray load(QString path);
    QString path();

  private:
    QString cachePath() const;

    // Path in the OS filesystem.
    QString phys_path;
    QHash<QString, unsigned int> cached_paths;
    const bit7z::Bit7zLibrary context;
    bit7z::BitArchiveReader *handle;
};

#endif // MOUNT_H
