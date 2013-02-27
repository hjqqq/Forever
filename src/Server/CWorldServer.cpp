/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWorldServer.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#include "CWorldServer.h"
#include "AttributeSet.h"
#include "CPacketPlayerDataWG.h"

CWorldServer::CWorldServer(std::string machineName)
{
   m_machineName = machineName;
   m_pNetStreamList = new std::list<GP::NetStream *>();
   m_pPlayerList = new std::list<CPlayerServerID *>();
}

CWorldServer::~CWorldServer()
{
   std::list<GP::NetStream *>::iterator itNet = m_pNetStreamList->begin();
   while(itNet != m_pNetStreamList->end()) {
      (*itNet)->stopConnection();
      delete (*itNet);
      itNet++;
   }
   m_pNetStreamList->clear();
   delete m_pNetStreamList;
   m_pNetStreamList = NULL;

   std::list<CPlayerServerID *>::iterator itPlayer = m_pPlayerList->begin();
   while(itPlayer != m_pPlayerList->end()) {
      delete (*itPlayer);
      itPlayer++;
   }
   m_pPlayerList->clear();
   delete m_pPlayerList;
   m_pPlayerList = NULL;
}

void CWorldServer::init(int port)
{
   m_nameVector.push_back("�ѯu�i�R�p�C�Y");
   m_nameVector.push_back("�k�l�k�l�f�^");
   m_nameVector.push_back("o�³��Vo");
   m_nameVector.push_back("�k��");
   m_nameVector.push_back("�����E��");

   m_curUID = 0;
   m_listener.startListen(port);
}

void CWorldServer::work(HWND hWnd, float timePass)
{
   if(m_listener.isAccepted()) {
      GP::NetStream *pNetStream = new GP::NetStream();
      m_pNetStreamList->push_back(pNetStream);

      m_listener.transferAcceptStream(*pNetStream);
   }

   std::list<GP::NetStream *>::iterator it = m_pNetStreamList->begin();
   while(it != m_pNetStreamList->end()) {
      procGameServer((*it));
      it++;
   }
}

CPlayerServerID* CWorldServer::addPlayerServerID(GP::NetStream *pNetStream)
{
   std::string strName;
   if(m_curUID < 5)
      strName = m_nameVector.at((int)m_curUID);

   //�u�@¾�~���ݩ�
   BasicAttribute knightAttr;
   memset(&knightAttr, 0, sizeof(knightAttr));
   knightAttr.iSTR = 115;
   knightAttr.iVIT = 110;
   knightAttr.iDEX = 100;
   knightAttr.iAGI = 100;
   knightAttr.iINT = 90;
   knightAttr.iWIL = 105;

   CPlayerServerID *pNewPlayer = new CPlayerServerID(m_machineName, strName, m_curUID++, 1);
   pNewPlayer->setBasAttr(knightAttr);                   //�]�w���⬰�u�@�P
   pNewPlayer->setPosition(450.0f, 450.0f);              //�]�w�����m
   pNewPlayer->setTargetPosition(450.0f, 450.0f);        //�]�w����ؼЦ�m

   int stack = 10;
   int gridHP = -1;
   pNewPlayer->getBackpack()->addItem(37, stack, gridHP);//�]�w����I�]���e��: "�ͩR�Ĥ�" X 10

   stack = 10;
   int gridMP = -1;
   pNewPlayer->getBackpack()->addItem(38, stack, gridMP);//�]�w����I�]���e��: "�믫�Ĥ�" X 10

   stack = 1;
   int grid;
   pNewPlayer->getBackpack()->addItem(0, stack, grid);   //�]�w����I�]���e��: "�V�m�Ϊ��C" X 1

   pNewPlayer->wearToEquipSlot(CHEST, 1);                //�]�w����� "�V�m�Ϊ��ݯݥ�"
   pNewPlayer->wearToEquipSlot(LEGS, 2);                 //�]�w����� "�V�m�Ϊ��ݻL��"

   pNewPlayer->addSkill(0);                              //�]�w���⦳ "���q����" �ޯ�
   pNewPlayer->addSkill(1);                              //�]�w���⦳ "�r�P�@��" �ޯ�

   HotKeyItem newHotKeyItem;
   newHotKeyItem.iField = 0;
   newHotKeyItem.pSkill = pNewPlayer->getSkill(1);
   newHotKeyItem.pItem = NULL;
   newHotKeyItem.iBackpackGrid = -1;
   pNewPlayer->addHotKeyItem(newHotKeyItem);             //�]�w���� "1�ֱ���" �O "�r�P�@��" �ޯ�

   newHotKeyItem.iField = 8;
   newHotKeyItem.pSkill = NULL;
   newHotKeyItem.pItem = pNewPlayer->getBackpack()->getItem(gridHP);
   newHotKeyItem.iBackpackGrid = gridHP;
   pNewPlayer->addHotKeyItem(newHotKeyItem);             //�]�w���� "9�ֱ���" �O "�ͩR�Ĥ�" �D��

   newHotKeyItem.iField = 9;
   newHotKeyItem.pSkill = NULL;
   newHotKeyItem.pItem = pNewPlayer->getBackpack()->getItem(gridMP);
   newHotKeyItem.iBackpackGrid = gridMP;
   pNewPlayer->addHotKeyItem(newHotKeyItem);             //�]�w���� "0�ֱ���" �O "�믫�Ĥ�" �D��

   pNewPlayer->updateEquipAttr();                        //��s����]���˳����Y�������ݩʼƭ�
   pNewPlayer->m_pNetStream = pNetStream;

   m_pPlayerList->push_back(pNewPlayer);

   return pNewPlayer;
}

void CWorldServer::procGameServer(GP::NetStream *pNetStream)
{
   pNetStream->procPackage();
   GP::NetBuffer netBuff;
   while(pNetStream->getFullPackage(netBuff)) {
      CBasePacket *pPacket = (CBasePacket *)netBuff.getBuffer();
      if(pPacket->m_id == PACKET_PASSWORD_GW)
         onRecvPasswordGW(pNetStream, (CPacketPasswordGW *)pPacket);
   }
}

void CWorldServer::onRecvPasswordGW(GP::NetStream *pNetStream, CPacketPasswordGW *pPacket)
{
   CPlayerServerID *pNewPlayer = addPlayerServerID(pNetStream);

   CPacketPlayerDataWG packetPlayerDataWG;
   packetPlayerDataWG.pack(pPacket->m_netID, pNewPlayer);
   pNetStream->send(&packetPlayerDataWG, sizeof(packetPlayerDataWG));
}