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
#include "CPacketPlayerInit.h"
#include "CPacketPlayerData.h"
#include "CPacketTargetPos.h"
#include "CPacketMonsterData.h"
#include "CPacketTargetObject.h"
#include "CPacketActionEvent.h"
#include "CPacketUseSkill.h"
#include "CPacketBackpackData.h"
#include "CPacketEquipData.h"
#include "CPacketAdvAttrData.h"
#include "CPacketAddSkill.h"
#include "CPacketCanUseSkill.h"
#include "CPacketDead.h"
#include "CPacketPlayerDeadReset.h"
#include "CPacketNPCData.h"
#include "CPacketMoney.h"
#include "CPacketXP.h"
#include "CPacketCancelUseSkill.h"
#include "CPacketKeyActionEvent.h"

#include <network\gp_socket.h>

#ifdef _GAMEENGINE_2D_
#include "CFPS.h"
#include "CKeyMan.h"
#include "CWindowMan.h"
#include "CTargetInfoWnd.h"
#endif  // #ifdef _GAMEENGINE_2D_

/** @brief Client�ݹC���y�{���� */
class CGameClient
{
   public:
      enum {STATE_LOGIN,         // �Ĥ@���n�J
            STATE_CHANGE_LOGIN,  // ���������n�J
            STATE_PLAY};         // �}�l��

      CGameClient(std::string machineName);
      ~CGameClient();

      /** @brief Client�ݪ�l�� */
      void init();
      
      std::string getMachineName();

#ifdef _GAMEENGINE_2D_
      /** @brief Client���޿�B�� 
        *        �ܤ֨C�����30��, �̦n��������b60��
        * @param hWnd     Client�ݵ���
        * @param timePass �@��frame�X��
        * @param bActive  ���b��ܪ����� */
      void work(HWND hWnd, float timePass, bool bActive);
#elif _GAMEENGINE_3D_
      /** @brief Client���޿�B�� 
        *        �ܤ֨C�����30��, �̦n��������b60��
        * @param hWnd     Client�ݵ���
        * @param timePass �@��frame�X�� */
      void work(HWND hWnd, float timePass);
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

      GP::NetStream* getNetStream();

      /** @brief UI��l�� */
      virtual void initUI();

      /** @brief ���a��l�Ƹ��
        * @param pPacket    �ʥ] */
      virtual void onRecvPlayerInit(CPacketPlayerInit *pPacket);

      /** @brief ������L���a���
        * @param pPacket �ʥ] */
      virtual void onRecvPlayerData(CPacketPlayerData *pPacket);

      /** @brief �����Ǫ����
        * @param pPacket �ʥ] */
      virtual void onRecvMonsterData(CPacketMonsterData *pPacket);

      /** @brief �����󴫸˳Ƹ�� */
      virtual void onRecvEquipData(CPacketEquipData *pPacket);

      /** @brief �������`��� */
      virtual void onRecvDead(CPacketDead *pPacket);

      /** @brief �������a���`�᭫�� */
      virtual void onRecvPlayerDeadReset(CPacketPlayerDeadReset *pPacket);

      virtual void onRecvNPCData(CPacketNPCData *pPacket);

   private:
      /** @brief �C���Ĥ@���n�J���޿�B�� */
      void workLogin();

      /** @brief �C���}�l�����޿�B��
        * @param hWnd     Client�ݵ��� 
        * @param timePass �@��frame�X�� */
      void workPlay(HWND hWnd, float timePass);
      
      /** @brief �����ؼЪ�����m */
      void onRecvTargetPos(CPacketTargetPos *pPacket);

      /** @brief ������w���ӥؼЪ� */
      void onRecvTargetObject(CPacketTargetObject *pPacket);

      /** @brief �����n�o�X����ʧ@�T�� */
      void onRecvActionEvent(CPacketActionEvent *pPacket);

      /** @brief �����ϥέ��ӧޯ� */
      void onRecvUseSkill(CPacketUseSkill *pPacket);

      /** @brief �����I�]��� */
      void onRecvBackpackData(CPacketBackpackData *pPacket);

      /** @brief �����i���ݩʸ�� */
      void onRecvAdvAttrData(CPacketAdvAttrData *pPacket);

      /** @brief �����ǲߧޯ� */
      void onRecvAddSkill(CPacketAddSkill *pPacket);

      /** @brief �����i�H�ϥΧޯ�(Server�^��) */
      void onRecvCanUseSkill(CPacketCanUseSkill *pPacket);

      /** @brief ��������� */
      void onRecvMoney(CPacketMoney *pPacket);

      /** @brief �����g��ȸ�� */
      void onRecvXP(CPacketXP *pPacket);

      /** @brief ���������ϥΧޯ� */
      void onRecvCancelUseSkill(CPacketCancelUseSkill *pPacket);

      /** @brief ��������ʧ@�t�ΰT�� */
      void onRecvKeyActionEvent(CPacketKeyActionEvent *pPacket);

      std::string    m_machineName;     // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      CScene        *m_pScene;          // �C�������޲z
      GP::NetStream *m_pNetStream;      // ��Game Server�������s�u
      int            m_gameState;       // �C�����A
      bool           m_bSendLogin;

#ifdef _GAMEENGINE_2D_
      void doKeyControl();              // ���䱱��
      void doUI(HWND hWnd);

      CKeyMan         m_keyMan;          // ��L/�ƹ��ʱ��޲z��
      CWindowMan     *m_pWindowMan;      // �����޲z��
      CTargetInfoWnd *m_pTargetInfoWnd;  // �ؼе���
      bool            m_keyMove;
#endif  // #ifdef _GAMEENGINE_2D_
};

#endif  // #ifndef _CGAMECLIENT_H_