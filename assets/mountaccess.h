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

    void loadMounts(QStringList mount_paths)
    {
        QVector<Mount *> newly_loaded_mounts;
        for (QString path : mount_paths) {
            Mount *mount = nullptr;
            for (int i = 0; i < loaded_mounts.size(); ++i) {
                Mount *loaded_mount = loaded_mounts.at(i);
                if (loaded_mount->path() == path) {
                    loaded_mounts.remove(i);
                    mount = loaded_mount;
                    break;
                }
            }

            if (mount == nullptr) {
                mount = new Mount(path);
            }
            mount->load();
            newly_loaded_mounts.append(mount);
        }

        cleanupMounts();
        loaded_mounts = newly_loaded_mounts;
    }

  private:
    QVector<Mount *> loaded_mounts;

    MountAccess(QObject *parent = nullptr) :
        QObject{parent}
    {
    }
    ~MountAccess()
    {
        cleanupMounts();
    }

    void cleanupMounts()
    {
        for (Mount *mount : loaded_mounts) {
            mount->deleteLater();
        }
        loaded_mounts.clear();
    }
};
