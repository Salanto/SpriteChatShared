#ifndef COORDINATORTYPES_H
#define COORDINATORTYPES_H

#include "spritechatshared_global.h"

#include <QObject>

namespace CoordinatorTypes {
    Q_NAMESPACE_EXPORT(SPRITECHATSHARED_EXPORT)

    struct SPRITECHATSHARED_EXPORT ServerInfo
    {
        QString name;
        QString description;
        QString ip;
        int players;
        int ws_port = -1;
        int wss_port = -1;
        bool favorite = false;

        bool operator==(const ServerInfo &other) const
        {
            return ip == other.ip && ws_port == other.ws_port && wss_port == other.wss_port;
        }
    };

    enum DocumentType
    {
        SERVERS,
        PRIVACY,
        MOTD,
        VERSION
    };
    Q_ENUM_NS(DocumentType)
};

#endif // COORDINATORTYPES_H
