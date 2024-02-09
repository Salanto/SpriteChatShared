#ifndef ANIMATIONTYPES_H
#define ANIMATIONTYPES_H

#include "spritechatshared_global.h"

#include <QObject>

namespace AnimationTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    enum AnimationEvent
    {
        HIDELAYER,
        SHOWLAYER,
        ANIMATION,
        EFFECT,
        TEXT,
        SOUND,
        SPLASH,
        SHAKE,
        FLASH,
        COLOR,
        SPEED,
        FONT
    };

    enum AnimationFlag
    {
        FADE_IN,
        FADE_OUT,
        FOREGROUND,
        BACKGROUND
    };
    Q_DECLARE_FLAGS(AnimationFlags, AnimationFlag)
}
Q_DECLARE_OPERATORS_FOR_FLAGS(AnimationTypes::AnimationFlags)

#endif // ANIMATIONTYPES_H
