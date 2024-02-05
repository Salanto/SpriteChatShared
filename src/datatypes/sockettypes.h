#ifndef SOCKETTYPES_H
#define SOCKETTYPES_H

#include "spritechatshared_global.h"

#include <QObject>

namespace SocketTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    enum SocketMode
    {
        INSECURE,
        SECURE
    };
    Q_ENUM_NS(SocketMode);
}

#endif // SOCKETTYPES_H
