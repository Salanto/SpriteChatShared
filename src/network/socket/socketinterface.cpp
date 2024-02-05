#include "socketinterface.h"

SocketInterface::SocketInterface(QObject *parent) :
    QObject{parent}
{
}

void SocketInterface::close()
{
    socket->close(QWebSocketProtocol::CloseCodeNormal, "Socket disconnected.");
}

void SocketInterface::close(QWebSocketProtocol::CloseCode f_code)
{
    socket->close(f_code);
}

void SocketInterface::write(QByteArray data)
{
    socket->sendBinaryMessage(data);
}
