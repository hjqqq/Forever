/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameServer.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#include "CGameServer.h"
#include "LogWindow.h"
extern CLogWindow glog;

CGameServer::CGameServer() : CScene()
{
   m_pWorldStream = new GP::NetStream();
   m_pNetStreamList = new std::list<GP::NetStream *>();
   //m_pPlayerList = new std::list<CNetPlayer *>();
}

CGameServer::~CGameServer()
{
   if(m_pWorldStream != NULL) {
      m_pWorldStream->stopConnection();
      delete m_pWorldStream;
      m_pWorldStream = NULL;
   }

   std::list<GP::NetStream *>::iterator itNet = m_pNetStreamList->begin();
   while(itNet != m_pNetStreamList->end()) {
      (*itNet)->stopConnection();
      delete (*itNet);
      itNet++;
   }
   m_pNetStreamList->clear();
   delete m_pNetStreamList;
   m_pNetStreamList = NULL;

   /*std::list<CNetPlayer *>::iterator itPlayer = m_pPlayerList->begin();
   while(itPlayer != m_pPlayerList->end()) {
      delete (*itPlayer);
      itPlayer++;
   }
   m_pPlayerList->clear();
   delete m_pPlayerList;
   m_pPlayerList = NULL;*/
}

void CGameServer::init(int port)
{
   m_listener.startListen(port);
   glog("%s [SS] : Init. listen port = %d", getCurDateTime().c_str(), port);

   m_gameState = STATE_WORLDSERVER_LOGIN;
   m_bSendWSLogin = false;

   GP::NetAddress addr;
   addr.setIPPort("127.0.0.1:2000");
   m_pWorldStream->startConnect(addr);
   glog("%s [SS] : connect to world server. (0x%X)", getCurDateTime().c_str(), m_pWorldStream);
}

void CGameServer::work(HWND hWnd)
{
   if(m_gameState == STATE_WORLDSERVER_LOGIN)
      workWorldServerLogin();
   else if(m_gameState == STATE_SCENESERVER_WORK)
      workPlay();
}

#ifdef _GAMEENGINE_2D_
void CGameServer::draw(HDC hdc)
{
   Rectangle (hdc, 0, 0, 1024, 768) ;
   CScene::draw(hdc);
}
#endif  // #ifdef _GAMEENGINE_2D_

void CGameServer::workWorldServerLogin()
{
   m_pWorldStream->procPackage();
   if(m_pWorldStream->isConnected()) {
      if(m_bSendWSLogin == false) {
         /*CPacketSceneServerLogin packetSceneServerLogin(SCENE_POETA);
         m_pWorldStream->send(&packetSceneServerLogin, sizeof(packetSceneServerLogin));
         m_bSendWSLogin = true;
         log("%s [SS] [Send WorldServer] : �o�eCPacketSceneServerLogin�ʥ], �i���������A���i��n�J�ʧ@", getCurDateTime().c_str());*/
      }

      GP::NetBuffer netBuff;
      if(m_pWorldStream->getFullPackage(netBuff)) {
         /*CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
         if(pPacket->getPacketType() == PACKET_OK) {
            m_gameState = STATE_SCENESERVER_WORK;
            log("%s [SS] [Recv WorldServer] : ����CPacketOK�ʥ], �i���������A���n�J����", getCurDateTime().c_str());
         }*/
      }
   }
}

void CGameServer::workPlay()
{
   procWorldServer();
   procAccept();
   
   /*std::list<CNetPlayer *>::iterator it = m_pPlayerList->begin();
   while(it != m_pPlayerList->end()) {
      procNetPlayer((*it));

      if((*it)->getClientStream()->isConnected() == false) {
         // Client�_�u
         if((*it)->getPlayer() != NULL) {
            // �q�������������a
            removePlayer((*it)->getPlayer()->getUID());

            // Todo: �ٻݭn�o�e�T���i��World Server�������a���u

            it = m_pPlayerList->erase(it);
         }
      }
      else
         it++;
   }*/
}

void CGameServer::procWorldServer()
{
   m_pWorldStream->procPackage();
   if(m_pWorldStream->isConnected()) {
      GP::NetBuffer netBuff;
      if(m_pWorldStream->getFullPackage(netBuff)) {
         /*CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
         if(pPacket->getPacketType() == PACKET_PLAYER_DATA)
            onRecvPlayerData(m_pWorldStream, (CPacketPlayerData *)pPacket);*/
      }
   }
}

void CGameServer::procAccept()
{
   if(m_listener.isAccepted()) {
      GP::NetStream *pNetStream = new GP::NetStream();
      
      m_listener.transferAcceptStream(*pNetStream);
      m_pNetStreamList->push_back(pNetStream);
   }

   std::list<GP::NetStream *>::iterator it = m_pNetStreamList->begin();
   while(it != m_pNetStreamList->end()) {
      (*it)->procPackage();

      if((*it)->isConnected()) {
         GP::NetBuffer netBuff;
         if((*it)->getFullPackage(netBuff)) {
            /*CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
            if(pPacket->getPacketType() == PACKET_CHANGE_SCENE_LOGIN) {
               onRecvChangeSceneLogin((*it), (CPacketChangeSceneLogin *)pPacket);
               m_pNetStreamList->erase(it);
               break;
            }*/
         }
      }

      it++;
   }
}

/*void CGameServer::procNetPlayer(CNetPlayer *pNetPlayer)
{
   GP::NetStream *pNetStream = pNetPlayer->getClientStream();
   pNetStream->procPackage();
   if(pNetStream->isConnected()) {
      GP::NetBuffer netBuff;
      if(pNetStream->getFullPackage(netBuff)) {
         CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
         // Todo: �PClient�������ʥ]�B�z
      }
   }
}*/

/*void CGameServer::onRecvPlayerData(GP::NetStream *pNetStream, CPacketPlayerData *pPacket)
{
   // ���ͤ@�Ӫ��a (��ƥ��w)
   CPlayer *pPlayer = CScene::addPlayer(-1);

   long long netID;
   pPacket->unpack(&netID, pPlayer);  // ���o�ʥ]�������a���

   NETPLAYER_DATA netPlayerData;
   netPlayerData.netID         = netID;
   //netPlayerData.playerState   = STATE_WAIT_LOGIN_DATA;
   netPlayerData.pClientStream = NULL;                  // Client�ݳs�u
   netPlayerData.pPlayer       = pPlayer;

   CNetPlayer *pNetPlayer = new CNetPlayer();
   pNetPlayer->init(netPlayerData);
   m_pPlayerList->push_back(pNetPlayer);

   log("%s [SS] [Recv WorldServer] : ����CPacketPlayerData�ʥ], �إߪ��a���", getCurDateTime().c_str());
}*/

/*void CGameServer::onRecvChangeSceneLogin(GP::NetStream *pNetStream, CPacketChangeSceneLogin *pPacket)
{
   long long netID;
   pPacket->unpack(&netID);

   std::list<CNetPlayer *>::iterator it = m_pPlayerList->begin();
   while(it != m_pPlayerList->end()) {
      if((*it)->getNetID() == netID) {
         (*it)->setClientStream(pNetStream);

         log("%s [SS] [Recv 0x%X] : ����CPacketChangeSceneLogin�ʥ], �j�w���a�s�u�P���a���", getCurDateTime().c_str(), pNetStream);

         // �e���a��Ƶ�Client
         CPacketPlayerInit packetPlayerInit;
         packetPlayerInit.pack((*it)->getPlayer());
         pNetStream->send(&packetPlayerInit, sizeof(packetPlayerInit));

         log("%s [SS] [Send 0x%X] : �o�eCPacketPlayerInit�ʥ]", getCurDateTime().c_str(), pNetStream);

         break;
      }
      it++;
   }
}*/