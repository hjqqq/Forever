#ifndef _CPACKETPLAYERINIT_H_
#define _CPACKETPLAYERINIT_H_
#include "CBasePacket.h"
#include "CPlayer.h"
#include "CNetDataBackpack.h"
#include "CNetDataSkill.h"
#include "CNetDataEquip.h"
#include "CNetDataHotKey.h"

#ifdef _GAMEENGINE_3D_
#include "CPlayer3D.h"
#endif

class CPacketPlayerInit : public CBasePacket
{
   public:
      CPacketPlayerInit() : CBasePacket(PACKET_PLAYER_INIT)
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
      unsigned int      m_xp;             //�g���
      unsigned int      m_xpMax;	         //�̤j�g���
      long long         m_money;          //��

      CNetDataBackpack  m_vBackpack[BACK_MAX];    //�I�]
      CNetDataSkill     m_vSkill[SKILL_MAX];      //�ޯ�
      CNetDataEquip     m_mEquip[MAX_SLOT];	     //�˳���
      CNetDataHotKey    m_vHotKey[UI_HOTKEY_NUM]; //�ֱ�����
};

#endif  // #ifndef _CPACKETPLAYERINIT_H_