#ifndef MUSICTYPES_H
#define MUSICTYPES_H

#include "spritechatshared_global.h"

#include <QObject>

namespace MusicTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    enum MusicFlag
    {
        STOP = 0x0,
        FADE_IN = 0x1,
        FADE_OUT = 0x2,
        SYNC_TRACK = 0x3,
    };
    Q_DECLARE_FLAGS(MusicFlags, MusicFlag)
    Q_FLAGS(MusicFlags)
}
Q_DECLARE_OPERATORS_FOR_FLAGS(MusicTypes::MusicFlags)

#endif // MUSICTYPES_H
