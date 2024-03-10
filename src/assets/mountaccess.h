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
    static MountAccess *ref();

    MountAccess(QObject *parent = nullptr);
    ~MountAccess();

    void loadMounts(QStringList paths);

    std::optional<QByteArray> fetch(QString path);

  public slots:
    void handleMountError(MountError error, QString message);

  Q_SIGNALS:
    void errorOccurred(MountError error, QString message);

  private:
    QReadWriteLock lock;
    QVector<Mount *> loaded_mounts;

    void cleanupMounts();
};
