#ifndef _CBASEPACKET_H_
#define _CBASEPACKET_H_
#include "Common.h"

enum {
   PACKET_FIRST_LOGIN, PACKET_PASSWORD_GW, PACKET_PLAYER_DATA_WG, PACKET_PLAYER_INIT, // �n�J�y�{�ʥ]
   PACKET_PLAYER_DATA, // ���a��ƫʥ]
   PACKET_TARGET_POS,  // �ؼЦ�m�ʥ]
};

class CBasePacket
{
   public:
      int m_id;

      CBasePacket(int id) {
         m_id = id;
      }
};

#endif  // #ifndef _CBASEPACKET_H_