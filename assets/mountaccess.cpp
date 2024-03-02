#include "mountaccess.h"

#include <QReadLocker>
#include <QWriteLocker>

void MountAccess::loadMounts(QStringList mount_paths)
{
    QWriteLocker locker(&lock);
    QVector<Mount *> newly_loaded_mounts;
    for (const QString &path : mount_paths) {
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

std::optional<QByteArray> MountAccess::fetch(QString path)
{
    QReadLocker locker(&lock);
    for (Mount *l_mount : loaded_mounts) {
        if (l_mount->containsFile(path)) {
            return std::optional<QByteArray>(l_mount->fetchFile(path));
        }
    }
    return std::nullopt;
}
MountAccess::MountAccess(QObject *parent) :
    QObject{parent}
{}

void MountAccess::cleanupMounts()
{
    for (Mount *mount : loaded_mounts) {
        mount->deleteLater();
    }
    loaded_mounts.clear();
}
MountAccess::~MountAccess()
{
    cleanupMounts();
}
