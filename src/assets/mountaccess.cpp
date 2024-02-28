#include "mountaccess.h"
#include "mount.h"

#include <QDebug>

MountAccess::MountAccess()
{
    qDebug() << "Starting pathing cache";
}

MountAccess *MountAccess::ref()
{
    static MountAccess instance;
    return &instance;
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

void MountAccess::initialise(QStringList paths)
{
    qDebug() << "Initialising Mounting System";
    for (const QString &path : paths) {
        Mount *l_mount = new Mount(this, path);
        if (!l_mount->open()) {
            continue;
        }
        if (!l_mount->indexArchive()) {
            l_mount->saveIndex();
        }
        mounts.append(l_mount);
    }
}

void MountAccess::reloadPackages(QStringList package_paths)
{
    // Don't reopen when we already have an open handle.
    for (Mount *mount : mounts) {
        if (!package_paths.contains(mount->path())) {
            mounts.removeAll(mount);
            mount->deleteLater();
        }
        package_paths.removeAll(mount->path());
    }

    for (const QString &path : package_paths) {
        Mount *l_mount = new Mount(this, path);
        if (!l_mount->open()) {
            continue;
        }
        if (!l_mount->indexArchive()) {
            l_mount->saveIndex();
        }
        mounts.append(l_mount);
    }
}
