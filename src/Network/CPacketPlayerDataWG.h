#ifndef _CPACKETPLAYERDATAWG_H_
#define _CPACKETPLAYERDATAWG_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataBackpack.h"
#include "CNetDataSkill.h"
#include "CNetDataEquip.h"
#include "CNetDataHotKey.h"

class CPacketPlayerDataWG : public CBasePacket
{
   public:
      CPacketPlayerDataWG() : CBasePacket(PACKET_PLAYER_DATA_WG) 
      {
      }

      void pack(long long netID, CPlayer *pPlayer);
      void unpack(CPlayer *pPlayer);

   private:
      friend class CGameServer;

      long long         m_netID;
      long long         m_uid;            //�ߤ@�s��
      char              m_level;          //����
      std::string       m_strName;        //�W�r
      BasicAttribute    m_basAttr;        //�򥻼ƭ�
      AdvancedAttribute m_advAttr;        //�ݩ�
      FPOS              m_position;       //����X,Y�y�� (2D)
      FPOS              m_targetPosition; //�ؼ��IX,Y�y�� (2D)
      float             m_fDirection;     //�����V(���: ����), �f�ɰw��V���ର+, ���ɰw��V���ର-, ��V��0�O�¤U
      unsigned int      m_xp;             //�g���
      unsigned int      m_xpMax;	         //�̤j�g���
      long long         m_money;          //��

      CNetDataBackpack  m_vBackpack[BACK_MAX];    //�I�]
      CNetDataSkill     m_vSkill[SKILL_MAX];      //�ޯ�
      CNetDataEquip     m_mEquip[MAX_SLOT];	     //�˳���
      CNetDataHotKey    m_vHotKey[UI_HOTKEY_NUM]; //�ֱ�����
};

#endif  // #ifndef _CPACKETPLAYERDATAWG_H_