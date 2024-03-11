#ifndef AREATYPES_H
#define AREATYPES_H

#include "spritechatshared_global.h"

#include <QObject>

namespace AreaTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    // RGB classes are QtGUI...
    class SPRITECHATSHARED_EXPORT RGB
    {
      public:
        RGB fromString(const QString &value);
        QString toString() const;

        int red() const;
        void setRed(const int &value);

        int green() const;
        void setGreen(const int &value);

        int blue() const;
        void setBlue(const int &value);

      private:
        int c_red = 255;
        int c_green = 255;
        int c_blue = 255;
    };

    struct SPRITECHATSHARED_EXPORT LocationMetadata
    {
        int id;
        int playercount;
        QString event;
        RGB rgb_color;
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
