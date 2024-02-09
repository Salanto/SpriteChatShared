#ifndef AREATYPES_H
#define AREATYPES_H

#include "spritechatshared_global.h"

#include <QObject>

namespace AreaTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    // RGB classes are QtGUI...
    struct SPRITECHATSHARED_EXPORT RGB
    {
        int red;
        int green;
        int blue;
    };

    struct SPRITECHATSHARED_EXPORT LocationMetadata
    {
        int id;
        int playercount;
        QString event;
        RGB rgb_colour;
        QString background;
        QString description;
    };

    struct SPRITECHATSHARED_EXPORT SideEntry
    {
        QString side;
        QString image;
        QString overlay;
    };

}

#endif // AREATYPES_H
