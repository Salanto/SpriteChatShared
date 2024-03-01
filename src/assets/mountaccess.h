#ifndef MOUNTACCESS_H
#define MOUNTACCESS_H

#include "assettypes.h"
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

  Q_SIGNALS:
    void errorOccured(QString message);

  public Q_SLOTS:
    void loadMounts(const AssetTypes::MountList &mounts);

  private:
    MountAccess();
    void cleanup();
    QVector<Mount *> mounts;
};

#endif // MOUNTACCESS_H
