#ifndef ASSETTYPES_H
#define ASSETTYPES_H

#include <QDateTime>
#include <QObject>

#include "spritechatshared_global.h"

namespace AssetTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    struct SPRITECHATSHARED_EXPORT MountSave
    {
        QString path;
        bool enabled;
        QDateTime last_modified;
    };

    struct SPRITECHATSHARED_EXPORT MountData
    {
        QString path;
        QDateTime last_modified;
    };
    using MountList = QList<MountData>;

    enum MountState
    {
        INVALID,
        MODIFIED,
        UNMODIFIED
    };
}

#endif // ASSETTYPES_H
