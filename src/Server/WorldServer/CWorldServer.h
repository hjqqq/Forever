/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWorldServer.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/24 */
#ifndef _CWORLDSERVER_H_
#define _CWORLDSERVER_H_
#include "Common.h"
/*#include "CNetPlayer.h"
#include "CPacketOK.h"
#include "CPacketSceneServerLogin.h"
#include "CPacketFirstLogin.h"
#include "CPacketPlayerData.h"
#include "CPacketChangeScene.h"*/

#include <network\gp_socket.h>

class CWorldServer
{
   public:
      CWorldServer();
      ~CWorldServer();

      /** @brief ��l��
        * @param port port number */
      void init(int port);

      /** @brief �޿��s
        * @param hWnd window���� */
      void work(HWND hWnd);

   private:
      /** @brief �B�zClient�ݳs�u
        *        �o�̪�Client�|�����, �@�جO���a��Client, �@�جOSceneServer */
      void procAccept();

      /** @brief �B�zSceneServer���s�u */
      void procSceneServer();

      /** @brief SceneServer�n�J�ɪ��ʥ]�B�z
        * @param pNetStream SceneServer�������s�u
        * @param pPacket    �ʥ] */
      //void onRecvSceneServerLogin(GP::NetStream *pNetStream, CPacketSceneServerLogin *pPacket);

      /** @brief Client�n�J�ɪ��ʥ]�B�z
        * @param pNetStream Client�������s�u
        * @param pPacket    �ʥ] */
      //void onRecvFirstLogin(GP::NetStream *pNetStream, CPacketFirstLogin *pPacket);

      GP::NetListener             m_listener;
      long long                   m_curUID;           // �ثe��UID
      long long                   m_curNetID;         // �ثe������ID �ߤ@�s��
      std::list<GP::NetStream *> *m_pNetStreamList;   // �Ҧ��������s�u
      std::list<GP::NetStream *> *m_pSceneStreamList; // �Ҧ��������A���������s�u
      //std::list<CNetPlayer *>    *m_pPlayerList;      // �Ҧ����a
      std::map<SCENE_TYPE, GP::NetStream *> *m_pSceneTable;  // ������Ӫ�
};

#endif  // #ifndef _CWORLDSERVER_H_