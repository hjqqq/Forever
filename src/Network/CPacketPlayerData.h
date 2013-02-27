#ifndef _CPACKETPLAYERDATA_H_
#define _CPACKETPLAYERDATA_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataSkill.h"
#include "CNetDataEquip.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketPlayerData : public CBasePacket
{
   public:
      CPacketPlayerData() : CBasePacket(PACKET_PLAYER_DATA)
      {
      }

      long long getUID();
      void pack(CPlayer *pPlayer);
      void unpack(CPlayer *pPlayer);
#ifdef _GAMEENGINE_3D_
      void unpack(CPlayer3D *pPlayer3D);
#endif

   private:
      long long         m_uid;            //�ߤ@�s��
      char              m_level;          //����
      std::string       m_strName;        //�W�r
      BasicAttribute    m_basAttr;        //�򥻼ƭ�
      AdvancedAttribute m_advAttr;        //�ݩ�
      FPOS              m_position;       //����X,Y�y�� (2D)
      FPOS              m_targetPosition; //�ؼ��IX,Y�y�� (2D)
      float             m_fDirection;     //�����V(���: ����), �f�ɰw��V���ର+, ���ɰw��V���ର-, ��V��0�O�¤U

      CNetDataSkill     m_vSkill[SKILL_MAX];      //�ޯ�
      CNetDataEquip     m_mEquip[MAX_SLOT];	     //�˳���
};

#endif  // #ifndef _CPACKETPLAYERDATA_H_