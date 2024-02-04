#ifndef SOCKETTYPES_H
#define SOCKETTYPES_H

#include <QObject>

namespace SocketTypes {
    Q_NAMESPACE

    enum SocketMode
    {
        INSECURE,
        SECURE
    };
    Q_ENUM_NS(SocketMode);
}

#endif // SOCKETTYPES_H
