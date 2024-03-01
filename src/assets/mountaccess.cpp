#include "mountaccess.h"
#include "mount.h"

#include <QDebug>

MountAccess *MountAccess::ref()
{
    static MountAccess instance;
    return &instance;
}

MountAccess::MountAccess()
{
    qDebug() << "Starting pathing cache";
}

void MountAccess::loadMounts(const AssetTypes::MountList &mount_list)
{
    if (!mounts.isEmpty()) {
        cleanup();
    }

    for (const AssetTypes::MountSave &data : mount_list) {
        if (!data.enabled) {
            continue;
        }

        Mount *l_mount = new Mount(data, this);
        if (l_mount->state() == AssetTypes::INVALID) {
            l_mount->deleteLater();
            emit errorOccured(QString("Mount at %1 is in an invalid state").arg(data.path));
            continue;
        }
        qDebug() << "Mount at" << data.path << "had the state" << l_mount->state();
        mounts.append(l_mount);
    }
}

void MountAccess::cleanup()
{
    for (Mount *mount : mounts) {
        mount->deleteLater();
    }
    mounts.clear();
}

std::optional<QByteArray> MountAccess::load(QString path)
{
    for (Mount *mount : mounts) {
        if (!mount->contains(path)) {
            continue;
        }
        return std::optional<QByteArray>(mount->load(path));
    }
    return std::nullopt;
}
