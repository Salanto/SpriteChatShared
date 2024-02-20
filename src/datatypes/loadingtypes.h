#ifndef LOADINGTYPES_H
#define LOADINGTYPES_H

#include "spritechatshared_global.h"
#include <QMap>
#include <QObject>

namespace LoadingTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    enum LoadingState
    {
        AWAIT_RESPONSE = 0,
        PARSE_RESPONSE,
        POPULATE_AREAS,
        POPULATE_MUSIC,
        AWAIT_CHARACTERS,
        POPULATE_CHARACTERS
    };
    Q_ENUM_NS(LoadingState)
}

#endif // LOADINGTYPES_H
