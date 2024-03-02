#pragma once

#include "mount.h"
#include "spritechatshared_global.h"

#include <QObject>
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

    void loadMounts(QStringList mount_paths);
    std::optional<QByteArray> fetch(QString path);

  private:
    QVector<Mount *> loaded_mounts;

    MountAccess(QObject *parent = nullptr);
    ~MountAccess();

    void cleanupMounts();
};
