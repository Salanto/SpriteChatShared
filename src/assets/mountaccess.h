#pragma once

#include "mount.h"
#include "spritechatshared_global.h"

#include <QObject>
#include <QReadWriteLock>
#include <QVector>

class SPRITECHATSHARED_EXPORT MountAccess : public QObject
{
    Q_OBJECT

  public:
    static MountAccess *ref()
    {
        static MountAccess instance;
        return &instance;
    }

    MountAccess(QObject *parent = nullptr);
    ~MountAccess();

    void loadMounts(QStringList paths);

    bool canFetch()
    {
        return true;
    }
    std::optional<QByteArray> fetch(QString path);

  private:
    QReadWriteLock lock;
    QVector<Mount *> loaded_mounts;

    void cleanupMounts();
};
