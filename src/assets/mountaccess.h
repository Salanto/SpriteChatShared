#ifndef MOUNTACCESS_H
#define MOUNTACCESS_H

#include "spritechatshared_global.h"

#include <QObject>

class Mount;

class SPRITECHATSHARED_EXPORT MountAccess : public QObject
{
    Q_OBJECT

  public:
    ~MountAccess() = default;
    static MountAccess *ref();

    std::optional<QByteArray> load(QString path);
    void initialise(QStringList paths);

  private Q_SLOTS:
    void reloadPackages(QStringList package_paths);

  private:
    MountAccess();
    QVector<Mount *> mounts;
};

#endif // MOUNTACCESS_H
