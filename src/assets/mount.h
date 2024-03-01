#ifndef MOUNT_H
#define MOUNT_H

#include "assettypes.h"
#include "bit7z/bit7zlibrary.hpp"
#include "bit7z/bitarchivereader.hpp"
#include <QHash>
#include <QObject>

class Mount : public QObject
{
    Q_OBJECT

  public:
    explicit Mount(AssetTypes::MountData info, QObject *parent = nullptr);
    ~Mount();

    bool contains(QString file);
    QByteArray load(QString path);
    AssetTypes::MountState state();
    QString path();

  private:
    void loadCache();
    void saveCache();
    QString cachePath() const;
    bool open();

    // Path in the OS filesystem.
    AssetTypes::MountState mount_state = AssetTypes::INVALID;
    AssetTypes::MountData information;
    QHash<QString, unsigned int> cached_paths;
    const bit7z::Bit7zLibrary context;
    bit7z::BitArchiveReader *handle;
};

#endif // MOUNT_H
