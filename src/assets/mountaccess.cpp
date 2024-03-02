#include "mountaccess.h"

#include <QReadLocker>
#include <QWriteLocker>

void MountAccess::loadMounts(QStringList paths)
{
    QWriteLocker locker(&lock);
    QVector<Mount *> newly_loaded_mounts;
    for (const QString &path : paths) {
        qInfo() << "Loading mount at" << path;

        Mount *mount = nullptr;
        for (int i = 0; i < loaded_mounts.size(); ++i) {
            Mount *loaded_mount = loaded_mounts.at(i);
            if (loaded_mount->path() == path) {
                loaded_mounts.remove(i);
                mount = loaded_mount;
                break;
            }
        }

        try {
            if (mount == nullptr) {
                mount = new Mount(path);
            }

            if (!mount->load()) {
                qWarning() << "Failed to load mount at" << path;
                delete mount;
                continue;
            }

            qInfo() << "Finished loading" << path;
            newly_loaded_mounts.append(mount);
        } catch (std::exception &e) {
            qWarning() << e.what();
        }
    }

    cleanupMounts();
    loaded_mounts = newly_loaded_mounts;
}

std::optional<QByteArray> MountAccess::fetch(QString path)
{
    QReadLocker locker(&lock);
    for (Mount *mount : loaded_mounts) {
        if (mount->containsFile(path)) {
            return std::optional<QByteArray>(mount->fetchFile(path));
        }
    }
    return std::nullopt;
}

MountAccess::MountAccess(QObject *parent) :
    QObject{parent}
{
}

MountAccess::~MountAccess()
{
    QWriteLocker locker(&lock);
    cleanupMounts();
}

void MountAccess::cleanupMounts()
{
    for (Mount *mount : loaded_mounts) {
        mount->deleteLater();
    }
    loaded_mounts.clear();
}
