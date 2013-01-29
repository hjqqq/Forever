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
/*#include "CNetPlayer.h"
#include "CPacketSceneServerLogin.h"
#include "CPacketPlayerData.h"
#include "CPacketChangeSceneLogin.h"
#include "CPacketPlayerInit.h"*/

#include <network\gp_socket.h>

typedef enum tagSCENESERVER_STATE {
   STATE_WORLDSERVER_LOGIN,  // ��World Server��login
   STATE_SCENESERVER_WORK    // work
} SCENESERVER_STATE;  // �C�����A

class CGameServer : public CScene
{
   public:
      CGameServer();
      ~CGameServer();

      /** @brief ��l��
        * @param port ���x���A����listen port */
      void init(int port);

      /** @brief �޿��s
        * @param hWnd �D���� */
      void work(HWND hWnd);

#ifdef _GAMEENGINE_2D_
      /** @brief 2Dø��
        * @param hDC ø�ϰ� */
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   private:
      /** @brief �B�z��WorldServer��Login */
      void workWorldServerLogin();

      /** @brief �B�z���C�����޿� */
      void workPlay();

      /** @brief �B�z�PWorldServer�����������s�u */
      void procWorldServer();

      /** @brief �B�z�PClient�����������s�u */
      void procAccept();

      /** @brief �B�z�PClient�������ʥ] */
      //void procNetPlayer(CNetPlayer *pNetPlayer);

      /** @brief �������a���
        * @param pNetStream WorldServer�������s�u
        * @param pPacket    �ʥ] */
      //void onRecvPlayerData(GP::NetStream *pNetStream, CPacketPlayerData *pPacket);

      /** @brief �����󴫳����n�J
        * @param pNetStream Client�������s�u
        * @param pPacket    �ʥ] */
      //void onRecvChangeSceneLogin(GP::NetStream *pNetStream, CPacketChangeSceneLogin *pPacket);

      GP::NetListener             m_listener;
      GP::NetStream              *m_pWorldStream;   // World Server�������s�u
      SCENESERVER_STATE           m_gameState;      // ���x���A�����C�����A
      bool                        m_bSendWSLogin;   // �O�_�e�Xlogin�ʥ]��world server
      std::list<GP::NetStream *> *m_pNetStreamList; // �Ҧ��������s�u
      //std::list<CNetPlayer *>    *m_pPlayerList;    // ���������Ҧ��������a
};

#endif  // #ifndef _CGAMESERVER_H_