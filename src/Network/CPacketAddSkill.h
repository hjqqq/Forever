#ifndef _CPACKETADDSKILL_H_
#define _CPACKETADDSKILL_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataSkill.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketAddSkill : public CBasePacket
{
   public:
      CPacketAddSkill() : CBasePacket(PACKET_ADD_SKILL)
      {
      }

      long long getUID();
      void pack(CPlayer *pPlayer, int skillID);
      void unpack(CPlayer *pPlayer);

   private:
      long long         m_uid;      //�ߤ@�s��
      CNetDataSkill     m_vSkill;   //�ޯ�
};

#endif  // #ifndef _CPACKETADDSKILL_H_