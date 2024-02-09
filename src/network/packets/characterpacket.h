#ifndef CHARACTERPACKET_H
#define CHARACTERPACKET_H

#include "selectcharacterpacket.h"

class SPRITECHATSHARED_EXPORT CharacterPacket : public SelectCharacterPacket
{
  public:
    CharacterPacket();

    QString header() const override;
};

#endif // CHARACTERPACKET_H
