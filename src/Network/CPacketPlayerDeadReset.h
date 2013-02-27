#ifndef _CPACKETPLAYERDEADRESET_H_
#define _CPACKETPLAYERDEADRESET_H_
#include "CBasePacket.h"
#include "CPlayer.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketPlayerDeadReset : public CBasePacket
{
   public:
      CPacketPlayerDeadReset() : CBasePacket(PACKET_PLAYER_DEAD_RESET)
      {
      }

      long long getUID();
      long long getTargetUID();
      void pack(CPlayer *pPlayer);
      void unpack(CPlayer *pPlayer);
#ifdef _GAMEENGINE_3D_
      void unpack(CPlayer3D *pPlayer3D);
#endif

   private:
      long long         m_uid;            //�ߤ@�s��
      FPOS              m_position;       //����X,Y�y�� (2D)
      FPOS              m_targetPosition; //�ؼ��IX,Y�y�� (2D)
      float             m_fDirection;     //�����V(���: ����), �f�ɰw��V���ର+, ���ɰw��V���ର-, ��V��0�O�¤U
      long long         m_targetUID;      //�ؼЪ�
};

#endif  // #ifndef _CPACKETPLAYERDEADRESET_H_