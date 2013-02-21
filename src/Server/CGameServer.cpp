/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameServer.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#include "CGameServer.h"
#include "CSkill.h"
#include "CWeaponInfo.h"
#include "CArmorInfo.h"
#include "CConsumableInfo.h"
#include "CPacketPasswordGW.h"
#include "CPacketPlayerInit.h"
#include "CPacketPlayerData.h"
#include "CPacketMonsterData.h"
#include "CPacketTargetObject.h"
#include "CPacketActionEvent.h"
#include "CPacketUseSkill.h"
#include "CPacketBackpackData.h"
#include "CPacketAdvAttrData.h"
#include "CPacketAddSkill.h"
#include "CPacketNPCData.h"

#ifdef _DEBUGLOG
#include "LogWindow.h"
extern CLogWindow glog;
#endif  // #ifdef _DEBUG

const int idelRandRange = 500;

CGameServer::CGameServer(std::string machineName) : CScene(machineName)
{
   m_machineName = machineName;
   m_pWorldStream = new GP::NetStream();
   m_pNetPlayerList = new std::list<CNetPlayer *>();
   srand((unsigned int)time(NULL));
}

CGameServer::~CGameServer()
{
   if(m_pWorldStream != NULL) {
      m_pWorldStream->stopConnection();
      delete m_pWorldStream;
      m_pWorldStream = NULL;
   }

   std::list<CNetPlayer *>::iterator itNetPlayer = m_pNetPlayerList->begin();
   while(itNetPlayer != m_pNetPlayerList->end()) {
      delete (*itNetPlayer);
      itNetPlayer++;
   }
   m_pNetPlayerList->clear();
   delete m_pNetPlayerList;
   m_pNetPlayerList = NULL;
}

void CGameServer::init(int port)
{
   CScene::addSceneMonsterEventListener(this);

   m_port = port;
   m_curUID = 3000;  // �n�׶}World Server����UID, �o�̪�m_curUID�u���Ǫ��Ϊ���
   m_curNetID = 0;
   m_listener.startListen(port);

   GP::NetAddress addr;
   addr.setIPPort("127.0.0.1:2000");
   m_pWorldStream->startConnect(addr);

   if(m_port == 2200) {  // �Ĥ@�ӳ���
      // ���ͩǪ�
      for(int i = 0; i < MONSTERAREA_INFO::getInfoCount(); i++) {
         CMonsterArea *pMonsterArea = m_monsterMap.addArea();
         pMonsterArea->create(i);
      }

      // Todo: ����NPC
		addNPC(this->generateUID(), 0, 300, 600);
   }
}

void CGameServer::work(HWND hWnd, float timePass)
{
   CScene::work(timePass);

   procWorldServer();
   procAccept();
   
   m_monsterMap.work(this, this);

   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      procNetPlayer((*it));  // ��client���ʥ]

      if((*it)->m_pNetStream->isConnected() == false) {  // �����_�u
         if((*it)->m_pPlayer != NULL)
            this->removePlayer((*it)->m_pPlayer->getUID());
         it = m_pNetPlayerList->erase(it);
      }
      else
         it++;
   }
}

long long CGameServer::generateUID()
{
	return m_curUID++;
}

#ifdef _GAMEENGINE_2D_
void CGameServer::draw(HDC hdc)
{
   m_monsterMap.draw(hdc);
   CScene::draw(hdc);
}
#endif  // #ifdef _GAMEENGINE_2D_

void CGameServer::updateAddMonster(CMonster *pMonster)
{
   CPacketMonsterData packet;
   packet.pack(pMonster);
   sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a
}

void CGameServer::updateMonsterTargetObject(CMonster *pMonster, long long newTargetObjectUID)
{
   CUnitObject *pNewTargetObject = this->getUnitObject(newTargetObjectUID);
   pMonster->setTargetObject(pNewTargetObject);

   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      CPacketTargetObject packet;
      packet.pack(pMonster);
      (*it)->m_pNetStream->send(&packet, sizeof(packet));
      it++;
   }
}

void CGameServer::updatePlayerBackpack(CBackpack *pBackpack)
{
   // ���Y���a���I�]����s
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it)->m_pPlayer->getBackpack() == pBackpack) {
         CPacketBackpackData packet;
         packet.pack((*it)->m_pPlayer);
         (*it)->m_pNetStream->send(&packet, sizeof(packet));
         break;
      }

      it++;
   }
}

void CGameServer::updatePlayerEquip(CPlayer *pPlayer, EquipSlot equipSlot, int itemId)
{
   // ���Y���a�˳Ƨ�
   CPacketEquipData packet;
   packet.pack(pPlayer, equipSlot, itemId);
   sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a
}

void CGameServer::updateAdvAttr(CUnitObject *pUnitObject)
{
   // ���i��O���a�]���i��O�Ǫ�

   CPacketAdvAttrData packet;
   packet.pack(pUnitObject);
   sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a

   // Todo : HP = 0, ���`�B�z
   if(pUnitObject->getAdvAttr().iHP <= 0) {

   }
}

void CGameServer::updateAddSkill(CUnitObject *pUnitObject, int skillID)
{
   CPlayer *pPlayer = dynamic_cast<CPlayer *>(pUnitObject);
   if(pPlayer == NULL)
      return;

   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it)->m_pPlayer == pPlayer) {
         CPacketAddSkill packet;
         packet.pack(pPlayer, skillID);
         (*it)->m_pNetStream->send(&packet, sizeof(packet));
         break;
      }

      it++;
   }
}

void CGameServer::updateSkillAvailable(CSkill *pSkill)
{
   // ��������B�z
}

void CGameServer::updateSkillCoolDown(CSkill *pSkill)
{
}

void CGameServer::updateFightActionEvent(CUnitObject *pUnitObject, CActionEvent *pActEvent)
{
   CPacketActionEvent packet;
   packet.pack(pUnitObject, pActEvent);
   sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a
}

void CGameServer::updateFightTargetPosition(CUnitObject *pUnitObject)
{
   CPacketTargetPos packet;
#ifdef _GAMEENGINE_3D_
   packet.pack(pUnitObject);
#elif _GAMEENGINE_2D_
   packet.pack(pUnitObject, true);
#endif
   sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a   
}

void CGameServer::updateMonsterAI(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   if(pMonster->getState() == IDLE)
      doMonsterAIIdle(pMonster);
   else if(pMonster->getState() == GOALS)
      doMonsterAIGoals(pMonster);
   else if(pMonster->getState() == DOLLY)
      doMonsterAIDolly(pMonster);
   else if(pMonster->getState() == RETURN)  //�^�k��� �ˬd��F�S ��F�}�lidle
      doMonsterAIReturn(pMonster);
   else if(pMonster->getState() == ATTACK)
      doMonsterAIAttack(pMonster);
}

void CGameServer::doMonsterAIIdle(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   if(pMonsterInfo->getATKtype() == MONSTER_ACTIVE) {
      std::list<CPlayer*>* playerList = this->getAllPlayer();
      std::list<CPlayer*>::iterator it = playerList->begin();
      float distance = pMonsterInfo->getAlert();
      long long playerID = -1;
      while(it != playerList->end()) {
         float dis = getDistance(pMonster->getPosition().fX, pMonster->getPosition().fY,
                                 (*it)->getPosition().fX, (*it)->getPosition().fY);
         if(dis < pMonsterInfo->getAlert()) {
            if(dis < distance) {
               distance = dis;
               playerID = (*it)->getUID();
            }
         }
         it++;
      }

      if(playerID > -1) {
         pMonster->addHate(playerID, 0);
         return;
      }
   }

   if(pMonster->isReachTarget()) {
      int pass = rand() % idelRandRange;
      if(pass == 3) {
         float range = pMonsterInfo->getAlert();
         int fx = (rand() % (int) (range * 2)) - (int) (range);
         int fy = (rand() % (int) (range * 2)) - (int) (range);
         float ftx = pMonster->getBornPosition().fX + fx;
         float fty = pMonster->getBornPosition().fY + fy;
         moveMonster(pMonster, ftx, fty);
      }
   }
}

void CGameServer::doMonsterAIGoals(CMonster *pMonster)
{
   CUnitObject* pUnitObject = pMonster->getTargetObject();
   if(pUnitObject == NULL)
      return;

   float fx = pUnitObject->getPosition().fX;
   float fy = pUnitObject->getPosition().fY;
   moveMonster(pMonster, fx, fy);

   pMonster->setState(DOLLY);
}

void CGameServer::doMonsterAIDolly(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   CUnitObject* pUnitObject = pMonster->getTargetObject();
   if(pUnitObject == NULL)
      return;

   float fx = pUnitObject->getPosition().fX;
   float fy = pUnitObject->getPosition().fY;
   moveMonster(pMonster, fx, fy);

   //�ؼЪ����}�ӻ��Ǫ��^�k
   if(pMonster->isMonsterTargetTooFarAway() == true) {
      moveMonster(pMonster, pMonster->getAnchorPosition().fX, pMonster->getAnchorPosition().fY);
      return;
   }

	float distance = getDistance(pMonster->getPosition().fX, pMonster->getPosition().fY, fx, fy);

   //���o�Ǫ����q�����ޯ�
   std::vector<int> vMonsterSkillID = pMonsterInfo->getSkill();
   std::vector<int>::iterator itSkillID = vMonsterSkillID.begin();
   CSkill *pSkill = pMonster->getSkill((*itSkillID));
   
   if(distance < pSkill->getInfo()->getCastRange()) {
      CActionEvent actEvent;
      actEvent.m_event = AET_REACH;
      CActionDispatch::getInstance()->sendEvnet(pMonster->getMachineName(), pMonster->getUID(), actEvent);

      CPacketActionEvent packet;
      packet.pack(pMonster, &actEvent);
      sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a

      pMonster->setState(ATTACK);
   }
}

void CGameServer::doMonsterAIReturn(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   pMonster->setAdvAttr(pMonsterInfo->getAdvAttr());
   // Todo: �n�B�z�Ǫ�HP,MP�ʥ]

   if(pMonster->isReachTarget())
      pMonster->setState(IDLE);
}

void CGameServer::doMonsterAIAttack(CMonster *pMonster)
{
   CMonsterInfo* pMonsterInfo = pMonster->getInfo();
   if(pMonsterInfo == NULL)
      return;

   std::vector<CSkill*> vSkill = pMonster->getSkill();
   float castRange = -1.0f;
   switch(pMonsterInfo->getWistom()) {
      case 1: {  // �u�ϥδ��q����
         std::vector<CSkill *>::iterator itSkill = vSkill.begin();
         if(itSkill != vSkill.end()) {
            castRange = (*itSkill)->getInfo()->getCastRange();

            if((*itSkill)->isReady()) {
               CPacketUseSkill packet;
               packet.pack(pMonster, (*itSkill)->getID());
               sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a

               pMonster->startCastSkill((*itSkill)->getID());
            }
         }
         break;
      }

      case 2:  
      case 3: {
         int skillIdx = 1;
         if(vSkill.size() > 2)
            skillIdx = rand() % vSkill.size();

         if(skillIdx < (int)vSkill.size()) {
            CSkill *pSkill = vSkill.at(skillIdx);
            castRange = pSkill->getInfo()->getCastRange();

            if(pSkill->isReady()) {
               CPacketUseSkill packet;
               packet.pack(pMonster, pSkill->getID());
               sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a

               pMonster->startCastSkill(pSkill->getID());
            }
            else {
               // ��δ��q����
               pSkill = vSkill.at(0);
               castRange = pSkill->getInfo()->getCastRange();

               if(pSkill->isReady()) {
                  CPacketUseSkill packet;
                  packet.pack(pMonster, pSkill->getID());
                  sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a

                  pMonster->startCastSkill(pSkill->getID());
               }
            }
         }
         break;
      }
   }

   float fx = pMonster->getTargetObject()->getPosition().fX;
   float fy = pMonster->getTargetObject()->getPosition().fY;
   float distance = getDistance(pMonster->getPosition().fX, pMonster->getPosition().fY, fx, fy);

   if(distance > castRange) {
      pMonster->setState(GOALS);
      return;
   }
}

void CGameServer::moveMonster(CMonster *pMonster, float x, float y)
{
#ifdef _GAMEENGINE_3D_
   pMonster->setTargetPosition(x, y);
#elif _GAMEENGINE_2D_
   pMonster->setTargetPosition(x, y, true);
#endif

   CPacketTargetPos packet;
#ifdef _GAMEENGINE_3D_
   packet.pack(pMonster);
#elif _GAMEENGINE_2D_
   packet.pack(pMonster, true);
#endif
   sendPacket(NULL, &packet, sizeof(packet));  // �e���Ҧ����a

	CActionEvent actEvent;
	actEvent.m_event = AET_NOT_REACH;
	CActionDispatch::getInstance()->sendEvnet(m_machineName, pMonster->getUID(), actEvent);
}

void CGameServer::procAccept()
{
   if(m_listener.isAccepted()) {
      CNetPlayer *pNetPlayer = new CNetPlayer();
      pNetPlayer->m_state = CNetPlayer::STATE_WAIT_LOGIN_DATA;
      pNetPlayer->m_netID = m_curNetID++;
      m_pNetPlayerList->push_back(pNetPlayer);

      m_listener.transferAcceptStream(*(pNetPlayer->m_pNetStream));
   }
}

void CGameServer::procWorldServer()
{
   m_pWorldStream->procPackage();
   GP::NetBuffer netBuff;
   while(m_pWorldStream->getFullPackage(netBuff)) {
      CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
      if(pPacket->m_id == PACKET_PLAYER_DATA_WG)
         onRecvPlayerDataWG((CPacketPlayerDataWG *)pPacket);
   }
}

void CGameServer::procNetPlayer(CNetPlayer *pNetPlayer)
{
   pNetPlayer->m_pNetStream->procPackage();

   if(pNetPlayer->m_pNetStream->isConnected() == true) {
      GP::NetBuffer netBuff;
      if(pNetPlayer->m_state == CNetPlayer::STATE_WAIT_LOGIN_DATA) {
         while(pNetPlayer->m_pNetStream->getFullPackage(netBuff)) {
            CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            if(pPacket->m_id == PACKET_FIRST_LOGIN)
               onRecvFirstLogin(pNetPlayer, (CPacketFirstLogin *)pPacket);
         }
      }
      else if(pNetPlayer->m_state == CNetPlayer::STATE_PLAY) {
         while(pNetPlayer->m_pNetStream->getFullPackage(netBuff)) {
            CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            if(pPacket->m_id == PACKET_TARGET_POS)
               onRecvTargetPos(pNetPlayer, (CPacketTargetPos *)pPacket);
            else if(pPacket->m_id == PACKET_USE_ITEM)
               onRecvUseItem(pNetPlayer, (CPacketUseItem *)pPacket);
            else if(pPacket->m_id == PACKET_EQUIP_DATA)
               onRecvShedEquip(pNetPlayer, (CPacketEquipData *)pPacket);
            else if(pPacket->m_id == PACKET_CAN_USE_SKILL)
               onRecvCanUseSkill(pNetPlayer, (CPacketCanUseSkill *)pPacket);
            else if(pPacket->m_id == PACKET_CANCEL_USESKILL)
               onRecvCancelUseSkill(pNetPlayer, (CPacketCancelUseSkill *)pPacket);
         }
      }
   }
}

CNetPlayer* CGameServer::getNetPlayer(long long netID)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it)->m_netID == netID)
         return (*it);

      it++;
   }

   return NULL;
}

void CGameServer::sendPlayerDataToOtherClient(CNetPlayer *pNetPlayer)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it) != pNetPlayer) {
         CPacketPlayerData packet;
         packet.pack(pNetPlayer->m_pPlayer);
         (*it)->m_pNetStream->send(&packet, sizeof(packet));
      }

      it++;
   }
}

void CGameServer::sendNearPlayerToClient(CNetPlayer *pNetPlayer)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it)->m_state == CNetPlayer::STATE_PLAY) {
         if((*it) != pNetPlayer) {
            CPacketPlayerData packet;
            packet.pack((*it)->m_pPlayer);
            pNetPlayer->m_pNetStream->send(&packet, sizeof(packet));
         }
      }

      it++;
   }
}

void CGameServer::sendNearMonsterToClient(CNetPlayer *pNetPlayer)
{
   std::list<CMonster *> *pMonsterList = this->getAllMonster();
   std::list<CMonster *>::iterator it = pMonsterList->begin();
   while(it != pMonsterList->end()) {
      CPacketMonsterData packet;
      packet.pack((*it));
      pNetPlayer->m_pNetStream->send(&packet, sizeof(packet));

      it++;
   }
}

void CGameServer::sendNearNPCToClient(CNetPlayer *pNetPlayer)
{
	std::vector<CNPC *> *pNPCList = this->getAllNPC();
	std::vector<CNPC *>::iterator it = pNPCList->begin();
	while(it != pNPCList->end()) {
		CPacketNPCData packet;
		packet.pack((*it));
		pNetPlayer->m_pNetStream->send(&packet, sizeof(packet));
		it++;
	}
}

void CGameServer::sendPacket(CNetPlayer *pNetPlayer, void *pPacket, int packetSize)
{
   std::list<CNetPlayer *>::iterator it = m_pNetPlayerList->begin();
   while(it != m_pNetPlayerList->end()) {
      if((*it) != pNetPlayer)
         (*it)->m_pNetStream->send(pPacket, packetSize);
      it++;
   }
}

void CGameServer::onRecvFirstLogin(CNetPlayer *pNetPlayer, CPacketFirstLogin *pPacket)
{
   CPacketPasswordGW packetPasswordGW;
   packetPasswordGW.m_netID = pNetPlayer->m_netID;
   pNetPlayer->m_state = CNetPlayer::STATE_WAIT_PLAYER_DATA;
   m_pWorldStream->send(&packetPasswordGW, sizeof(packetPasswordGW));
}

void CGameServer::onRecvPlayerDataWG(CPacketPlayerDataWG *pPacket)
{
   // ���ͤ@�Ӫ��a (��ƥ��w)
   CPlayer *pNewPlayer = CScene::addPlayer(pPacket->m_uid);
   pPacket->unpack(pNewPlayer);  // ���o�ʥ]�������a���
   
   pNewPlayer->addPlayerBackpackEventListener(this);   // ��ť���a�I�]�ܰʦ欰
   pNewPlayer->addPlayerEquipEventListener(this);      // ��ť���a�˳Ƨ󴫦欰
   pNewPlayer->addAdvAttrEventListener(this);          // ��ť���a�ݩ��ܰʦ欰
   pNewPlayer->addSkillEventListener(this);            // ��ť���a�ޯ��ܰʦ欰
   pNewPlayer->addFightEventListener(this);            // ��ť���a�԰��t���ܰʦ欰

   CNetPlayer *pNetPlayer = getNetPlayer(pPacket->m_netID);
   pNetPlayer->m_pPlayer = pNewPlayer;
   pNetPlayer->m_state = CNetPlayer::STATE_PLAY;

   // �e��Ƶ�Client
   CPacketPlayerInit packetPlayerInit;
   packetPlayerInit.pack(pNewPlayer);
   pNetPlayer->m_pNetStream->send(&packetPlayerInit, sizeof(packetPlayerInit));

   // �e�ۤv����Ƶ���Lclient
   sendPlayerDataToOtherClient(pNetPlayer);

   // �e��L���a����Ƶ��ۤv
   sendNearPlayerToClient(pNetPlayer);

   // �e�Ǫ���Ƶ�client
	sendNearMonsterToClient(pNetPlayer);

   // Todo: �٨S�B�z����
	sendNearNPCToClient(pNetPlayer);
}

void CGameServer::onRecvTargetPos(CNetPlayer *pNetPlayer, CPacketTargetPos *pPacket)
{
   pPacket->unpack(pNetPlayer->m_pPlayer);
   //sendPacket(pNetPlayer, pPacket, sizeof(*pPacket));
   sendPacket(NULL, pPacket, sizeof(*pPacket));
}

void CGameServer::onRecvUseItem(CNetPlayer *pNetPlayer, CPacketUseItem *pPacket)
{
   if(pNetPlayer->m_pPlayer->getUID() != pPacket->getUID())
      return;

   // �ˬd���a���S���Ӷ����~
   CBackpack *pBackpack = pNetPlayer->m_pPlayer->getBackpack();
   CItem *pItem = pBackpack->getItem(pPacket->getBackpackGrid());
   if(pItem == NULL)
      return;

   CItemInfo *pItemInfo = pItem->getInfo();
   if(pItemInfo == NULL)
      return;

   if(pItem->getID() != pPacket->getItemID())
      return;

   if(pItem->getStack() <= 0)
      return;

   pNetPlayer->m_pPlayer->useItem(pItem->getID());
}

void CGameServer::onRecvShedEquip(CNetPlayer *pNetPlayer, CPacketEquipData *pPacket)
{
   pPacket->unpack(pNetPlayer->m_pPlayer);
}

void CGameServer::onRecvCanUseSkill(CNetPlayer *pNetPlayer, CPacketCanUseSkill *pPacket)
{
   if(pNetPlayer->m_pPlayer->getUID() != pPacket->getUID())
      return;

   CUnitObject *pUnitObject = this->getUnitObject(pPacket->getTargetUID());
   pNetPlayer->m_pPlayer->setTargetObject(pUnitObject);
   bool bCanUse = pNetPlayer->m_pPlayer->canUseSkill(pPacket->getUseSkillID());
   
   pPacket->setCanUseSkill(bCanUse);
   pNetPlayer->m_pNetStream->send(pPacket, sizeof(*pPacket));

   if(bCanUse == true)
      pNetPlayer->m_pPlayer->startCastSkill(pPacket->getUseSkillID());
}

void CGameServer::onRecvCancelUseSkill(CNetPlayer *pNetPlayer, CPacketCancelUseSkill *pPacket)
{
   pPacket->unpack(pNetPlayer->m_pPlayer);
}