#ifndef CHARLISTTAKENPACKET_H
#define CHARLISTTAKENPACKET_H

#include "charlistpacket.h"

class SPRITECHATSHARED_EXPORT CharlistTakenPacket : public CharlistPacket
{
  public:
    CharlistTakenPacket();

    QString header() const override;
};

#endif // CHARLISTTAKENPACKET_H
