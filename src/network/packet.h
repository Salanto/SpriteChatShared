#ifndef PACKET_H
#define PACKET_H

#include <QString>

class Packet
{
public:
    Packet() = default;
    ~Packet() = default;

    QString header();
};

#endif // PACKET_H
