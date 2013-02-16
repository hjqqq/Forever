#ifndef _CBASEPACKET_H_
#define _CBASEPACKET_H_
#include "Common.h"

enum {
   PACKET_FIRST_LOGIN, PACKET_PASSWORD_GW, PACKET_PLAYER_DATA_WG, PACKET_PLAYER_INIT, // �n�J�y�{�ʥ]
   PACKET_PLAYER_DATA,   // ���a��ƫʥ]
   PACKET_TARGET_POS,    // �ؼЦ�m�ʥ]
   PACKET_MONSTER_DATA,  // �Ǫ���ƫʥ]
   PACKET_TARGET_OBJECT, // �ؼЪ��ʥ]
   PACKET_ACTION_EVENT,  // �ʧ@�t�ΰT��
   PACKET_USE_SKILL,     // �ϥΧޯ�
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