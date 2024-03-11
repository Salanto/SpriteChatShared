#ifndef SPRITECHATSHARED_GLOBAL_H
#define SPRITECHATSHARED_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SPRITECHATSHARED_LIBRARY
#define SPRITECHATSHARED_EXPORT Q_DECL_EXPORT
#else
#define SPRITECHATSHARED_EXPORT Q_DECL_IMPORT
#endif

enum class MountError
{
    CaughtException,
    FailedToLoadMount,
    FailedToIndexMount,
    FailedToResetMount,
    FailedToFetchFile,
    FailedToLoadCache,
    FailedToSaveCache,
};

#endif // SPRITECHATSHARED_GLOBAL_H
