#ifndef SERVERROUTER_H
#define SERVERROUTER_H

#include "abstractpacket.h"
#include "loadingtypes.h"
#include "serversocket.h"
#include "spritechatshared_global.h"

#include <QObject>
#include <QPointer>
#include <QWebSocketProtocol>
#include <memory>

class SPRITECHATSHARED_EXPORT ServerRouter : public QObject
{
    Q_OBJECT
    using Route = void (ServerRouter::*)(std::shared_ptr<AbstractPacket>);

  public:
    explicit ServerRouter(QObject *parent = nullptr);

    void connectToDataEndpoint(CoordinatorTypes::ServerInfo f_server);
    void connectToGameEndpoint(CoordinatorTypes::ServerInfo f_server);
    void connect(CoordinatorTypes::ServerInfo f_server, QString endpoint);

  signals:
    // State signals
    void connectedToData();
    void connectedToGame();
    void disconnected();
    void errorOccured(QString f_reason);

    // Internal routing signals for gameplay data.
    void backgroundReceived(std::shared_ptr<AbstractPacket> f_packet);
    void characterReceived(std::shared_ptr<AbstractPacket> f_packet);
    void charlistReceived(std::shared_ptr<AbstractPacket> f_packet);
    void charlistTakenReceived(std::shared_ptr<AbstractPacket> f_packet);
    void chatMessageReceived(std::shared_ptr<AbstractPacket> f_packet);
    void locationListReceived(std::shared_ptr<AbstractPacket> f_packet);
    void musiclistReceived(std::shared_ptr<AbstractPacket> f_packet);
    void musicReceived(std::shared_ptr<AbstractPacket> f_packet);
    void notificationReceived(std::shared_ptr<AbstractPacket> f_packet);
    void metaDataReceived(std::shared_ptr<AbstractPacket> f_packet);
    void sideReceived(std::shared_ptr<AbstractPacket> f_packet);
    void sideListReceived(std::shared_ptr<AbstractPacket> f_packet);
    void viewportAnimationReceived(std::shared_ptr<AbstractPacket> f_packet);

    // We should have a loading screen
    void loadingStep(LoadingTypes::LoadingState f_state);
    void t_loadingLocations(std::shared_ptr<AbstractPacket> f_packet);
    void t_loadingMusic(std::shared_ptr<AbstractPacket> f_packet);
    void t_loadingCharacters(std::shared_ptr<AbstractPacket> f_packet);

  public slots:
    void disconnect(QWebSocketProtocol::CloseCode f_code = QWebSocketProtocol::CloseCodeNormal, QString f_reason = "No reason provided.");
    void write(const QByteArray &f_data);

  private slots:
    void metadataTimeout();
    void receive(const QByteArray &f_data);
    void socketDisconnected();

    // wE sHoUlD hAvE a LoAdInG sCrEeN
    void loadingLocations(std::shared_ptr<AbstractPacket> f_packet);
    void loadingMusic(std::shared_ptr<AbstractPacket> f_packet);
    void loadingCharacters(std::shared_ptr<AbstractPacket> f_packet);

  private:
    void deleteSocket();
    bool canRoute(QString f_header);
    void route(std::shared_ptr<AbstractPacket> f_packet);
    QMap<QString, Route> routes;
    QPointer<ServerSocket> socket;

    QTimer *metadata_timeout;
};

#endif // SERVERROUTER_H
