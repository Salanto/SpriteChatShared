#ifndef SERVERTYPES_H
#define SERVERTYPES_H

#include <QObject>
#include <QVersionNumber>

namespace ServerTypes {
    Q_NAMESPACE

    struct CoordinatorServerData
    {
        QString name;
        QString ip;
        int ws_port;
        int wss_port;
    };

    struct ServerInformation
    {
        QString app_name;
        QVersionNumber app_version;
        QString name;
        QString description;
        QString ip;
        int playercount = 0;
        QString asset_url;
        QStringList package_ids;
    };
};

#endif // SERVERTYPES_H
