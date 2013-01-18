/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CGameClient.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/12 */
#ifndef _CGAMECLIENT_H_
#define _CGAMECLIENT_H_
#include "CScene.h"
//#include "CPacketFirstLogin.h"
//#include "CPacketChangeScene.h"
//#include "CPacketChangeSceneLogin.h"
//#include "CPacketPlayerInit.h"

//#include <network\gp_socket.h>

#ifdef _GAMEENGINE_2D_
#include "CFPS.h"
#include "CKeyMan.h"
#include "CWindowMan.h"
#include "CTargetInfoWnd.h"
#endif  // #ifdef _GAMEENGINE_2D_

//typedef enum tagGAME_STATE {
//   STATE_LOGIN,              // �Ĥ@���n�J
//   STATE_CHANGESCENE_LOGIN,  // ���������n�J
//   STATE_PLAY                // �}�l��
//} CLIENT_STATE;  // �C�����A

/** @brief Client�ݹC���y�{���� */
class CGameClient
{
   public:
      CGameClient();
      ~CGameClient();

      /** @brief Client�ݪ�l�� */
      void init();

#ifdef _GAMEENGINE_2D_
      /** @brief Client���޿�B�� 
        *        �ܤ֨C�����30��, �̦n��������b60��
        * @param hWnd Client�ݵ��� */
      void work(HWND hWnd);
#elif _GAMEENGINE_3D_
      /** @brief Client���޿�B�� 
        *        �ܤ֨C�����30��, �̦n��������b60��
        * @param timePass �@��frame�X��
        * @param hWnd     Client�ݵ��� */
      void work(float timePass, HWND hWnd);
#endif

#ifdef _GAMEENGINE_2D_
      /** @brief Client��ø�ϰʧ@ 
        * @param hdc ø�ϸ˸m */
      void draw(HDC hdc);
#endif  // #ifdef _GAMEENGINE_2D_

   protected:
      /** @brief ���o����
        * @return ���� */
      CScene* getScene();

      /** @brief UI��l�� */
      virtual void initUI();

   private:
      /** @brief �C���Ĥ@���n�J���޿�B�� */
      //void workLogin();

      /** @brief �C�������������n�J�޿�B��
        * @param hWnd Client�ݵ��� */
      //void workChangeSceneLogin();

      /** @brief �C���}�l�����޿�B��
        * @param timePass �@��frame�X��
        * @param hWnd     Client�ݵ��� */
      void workPlay(float timePass, HWND hWnd);

      /** @brief �����C������
        * @param pNetStream ��server�s�u
        * @param pPacket    �ʥ] */
      //void onRecvChangeScene(GP::NetStream *pNetStream, CPacketChangeScene *pPacket);

      /** @brief ���a��l��
        * @param pNetStream server�s�u
        * @param pPacket    �ʥ] */
      //void onRecvPlayerInit(GP::NetStream *pNetStream, CPacketPlayerInit *pPacket);

      CScene        *m_pScene;          // �C�������޲z
      //CLIENT_STATE   m_gameState;       // �C�����A
      //GP::NetStream *m_pNetStream;      // ��server�������s�u (WorldServer��SceneServer)
      //bool           m_bSendLogin;
      //long long      m_mainPlayerNetID; // ���a�������s��

#ifdef _GAMEENGINE_2D_
      void doKeyControl();              // ���䱱��
      void doUI(HWND hWnd);

      CFPS            m_fps;             // FPS���;�
      CKeyMan         m_keyMan;          // ��L/�ƹ��ʱ��޲z��
      CWindowMan     *m_pWindowMan;      // �����޲z��
      CTargetInfoWnd *m_pTargetInfoWnd;  // �ؼе���
      bool            m_mouseMove;
      bool            m_keyMove;
#endif  // #ifdef _GAMEENGINE_2D_
};

#endif  // #ifndef _CGAMECLIENT_H_