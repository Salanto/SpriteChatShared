#include "socketinterface.h"

SocketInterface::SocketInterface(QObject *parent) :
    QObject{parent}
{
}

void SocketInterface::close()
{
    ws_socket->close(QWebSocketProtocol::CloseCodeNormal, "Socket disconnected.");
}

void SocketInterface::write(QByteArray data)
{
    ws_socket->sendBinaryMessage(data);
}
