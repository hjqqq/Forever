/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameServer.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#ifndef _CGAMESERVER_H_
#define _CGAMESERVER_H_
#include "CScene.h"
#include "CFPS.h"
#include "CNetPlayer.h"
#include "CMonsterMap.h"
#include "CPacketFirstLogin.h"
#include "CPacketPlayerDataWG.h"
#include "CPacketTargetPos.h"
#include "CPacketUseItem.h"
#include "CPacketEquipData.h"
#include "CPacketCanUseSkill.h"
#include "CPacketCancelUseSkill.h"
#include "CPacketBuyItem.h"
#include "CPacketTargetObject.h"
#include "CPacketKeyActionEvent.h"
#include "IMonsterAIEventListener.h"
#include "ISceneMonsterEventListener.h"
#include "IPlayerBackpackEventListener.h"
#include "IPlayerEquipEventListener.h"
#include "IAdvAttrEventListener.h"
#include "ISkillEventListener.h"
#include "IFightEventListener.h"
#include "IDeadEventListener.h"
#include "IPlayerAttrEventListener.h"

#include <network\gp_socket.h>

class CGameServer : public CScene,
                    public IMonsterAIEventListener,
                    public ISceneMonsterEventListener,
                    public IPlayerBackpackEventListener,
                    public IPlayerEquipEventListener,
                    public IAdvAttrEventListener,
                    public ISkillEventListener,
                    public IFightEventListener,
                    public IDeadEventListener,
                    public IPlayerAttrEventListener
{
   public:
      CGameServer(std::string machineName);
      ~CGameServer();

      /** @brief ��l��
        * @param port ���x���A����listen port */
      void init(int port);

      /** @brief �޿��s
        * @param hWnd �D���� 
        * @param timePass �@��frame�X�� */
      void work(HWND hWnd, float timePass);

      long long generateUID();

#ifdef _GAMEENGINE_2D_
      /** @brief 2Dø��
        * @param hDC ø�ϰ� */
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      // IMonsterAIEventListener
      /* virtual */ void updateMonsterTargetObject(CMonster *pMonster, long long newTargetObjectUID);
      /* virtual */ void updateMonsterAI(CMonster *pMonster);

      // ISceneMonsterEventListener
      /* virtual */ void updateAddMonster(CMonster *pMonster);

      // IPlayerBackpackEventListener
      /* virtual */ void updatePlayerBackpack(CBackpack *pBackpack);

      // IPlayerEquipEventListener
      /* virtual */ void updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId);

      // IAdvAttrEventListener
      /* virtual */ void updateAdvAttr(CUnitObject *pUnitObject);

      // ISkillEventListener
      /* virtual */ void updateAddSkill(CUnitObject *pUnitObject, int skillID);
      /* virtual */ void updateSkillAvailable(CSkill *pSkill);
      /* virtual */ void updateSkillCoolDown(CSkill *pSkill);

      // IFightEventListener
      /* virtual */ void updateFightActionEvent(CUnitObject *pUnitObject, CActionEvent *pActEvent);
      /* virtual */ void updateFightTargetPosition(CUnitObject *pUnitObject);
      /* virtual */ void updateFightTargetDead(CUnitObject *pUnitObject, CUnitObject *pTargetObject);

      // IDeadEventListener
      /* virtual */ void updateDead(long long uid);

      // IPlayerAttrEventListener
      /* virtual */ void updatePlayerAttr(CPlayer *pPlayer, unsigned int offsetXP, long long offsetMoney);

      void doMonsterAIIdle(CMonster *pMonster);
      void doMonsterAIGoals(CMonster *pMonster);
      void doMonsterAIDolly(CMonster *pMonster);
      void doMonsterAIReturn(CMonster *pMonster);
      void doMonsterAIAttack(CMonster *pMonster);

      /** @brief �Ǫ����� */
      void moveMonster(CMonster *pMonster, float x, float y);

      /** @brief �B�z�PClient�����������s�u */
      void procAccept();

      /** @brief �B�z�PWorldServer�����������s�u */
      void procWorldServer();

      /** @brief �B�z�PClient�������ʥ] */
      void procNetPlayer(CNetPlayer *pNetPlayer);

      CNetPlayer* getNetPlayer(long long netID);

      void sendPlayerDataToOtherClient(CNetPlayer *pNetPlayer);
      void sendNearPlayerToClient(CNetPlayer *pNetPlayer);
      void sendNearMonsterToClient(CNetPlayer *pNetPlayer);
		void sendNearNPCToClient(CNetPlayer *pNetPlayer);

      /** @brief �NpNetPlayer����ưe����LClient */
      void sendPacket(CNetPlayer *pNetPlayer, void *pPacket, int packetSize);

      /** @brief ����Client�Ĥ@���n�J
        * @param pNetPlayer Client�ݪ��a
        * @param pPacket    �ʥ] */
      void onRecvFirstLogin(CNetPlayer *pNetPlayer, CPacketFirstLogin *pPacket);

      /** @brief �������a���(World Server�ǹL��)
        * @param pPacket    �ʥ] */
      void onRecvPlayerDataWG(CPacketPlayerDataWG *pPacket);

      /** @brief �������a�ؼЦ�m */
      void onRecvTargetPos(CNetPlayer *pNetPlayer, CPacketTargetPos *pPacket);

      /** @brief �������a�ϥΪ��~ */
      void onRecvUseItem(CNetPlayer *pNetPlayer, CPacketUseItem *pPacket);

      /** @brief �������U�˳� */
      void onRecvShedEquip(CNetPlayer *pNetPlayer, CPacketEquipData *pPacket);

      /** @brief �����ण��ϥΧޯ� */
      void onRecvCanUseSkill(CNetPlayer *pNetPlayer, CPacketCanUseSkill *pPacket);

      /** @brief ���������ϥΧޯ� */
      void onRecvCancelUseSkill(CNetPlayer *pNetPlayer, CPacketCancelUseSkill *pPacket);

      /** @brief �����R���~ */
      void onRecvBuyItem(CNetPlayer *pNetPlayer, CPacketBuyItem *pPacket);

      /** @brief �������a���ؼЪ� */
      void onRecvTargetObject(CNetPlayer *pNetPlayer, CPacketTargetObject *pPacket);

      /** @brief ��������ʧ@�T�� */
      void onRecvKeyActionEvent(CNetPlayer *pNetPlayer, CPacketKeyActionEvent *pPacket);

      std::string              m_machineName;     // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      int                      m_port;
      long long                m_curUID;
      long long                m_curNetID;
      GP::NetListener          m_listener;
      GP::NetStream           *m_pWorldStream;    // World Server�������s�u
      std::list<CNetPlayer *> *m_pNetPlayerList;  // ���������Ҧ��������a
      CMonsterMap              m_monsterMap;
};

#endif  // #ifndef _CGAMESERVER_H_