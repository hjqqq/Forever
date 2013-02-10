/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionSystem.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/21 */
#ifndef _CACTIONSYSTEM_H_
#define _CACTIONSYSTEM_H_
#include "CAction.h"
#include "CActionEvent.h"
#include "CNotifyActionEvent.h"
#include "IDrawWeaponNotifyListener.h"
#include "IPutinWeaponNotifyListener.h"
#include "IPlaySoundNotifyListener.h"

/** @brief �ʧ@�t�� 
  *        �i�Ω󪱮a�B�Ǫ��BNPC */
class CActionSystem
{
   public:
      CActionSystem(std::string machineName, long long uid);
      ~CActionSystem();
   
      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X�� */
      void work(float timePass);

      /** @brief �O�_���ܰʧ@
        * @return true - ���� / false - �S���� */
      bool isChangeAction();

      /** @brief ���o�ثe���ʧ@��T
        * @return �ʧ@��T */
      CAction* getCurAction();

      /** @brief �s�W�ʧ@��T
        * @param pAction �ʧ@��T */
      void addAction(CAction *pAction);

      /** @brief �O�_�i����
        * @return true - �i���� / false - ���i���� */
      bool isMove();

      /** @brief ���o�Ҧ��ʵe�W��
        * @return �Ҧ��ʵe�W�� */
      std::vector<std::string> getAllAnimationName();

#ifdef _GAMEENGINE_2D_
      /** @brief Client��ø�ϰʧ@ 
        * @param hdc ø�ϸ˸m
        * @param x   �n�e�b���̪�X�y��
        * @param y   �n�e�b���̪�Y�y�� */
      void draw(HDC hdc, int x, int y);
#endif

      /** @brief �s��
        * @param fileName �ɮצW�� */
      void write(std::string fileName);

      /** @brief Ū��
        * @param fileName �ɮצW�� */
      bool read(std::string fileName);

      void addDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);
      void removeDrawWeaponNotifyListener(IDrawWeaponNotifyListener *pListener);

      void addPutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);
      void removePutinWeaponNotifyListener(IPutinWeaponNotifyListener *pListener);

      void addPlaySoundNotifyListener(IPlaySoundNotifyListener *pListener);
      void removePlaySoundNotifyListener(IPlaySoundNotifyListener *pListener);

   private:
      /** @brief �����ʧ@
        * @param newActionID �s�ʧ@�s�� */
      void changeAction(int newActionID);

      /** @brief �H�e�ʧ@�T��
        * @param actEvent �ʧ@�T�� */
      void sendEvent(CActionEvent &actEvent);

      /** @brief �H�e�q���T��
        * @param pNotifyActionEvent �q���T�� */
      void sendNotify(CNotifyActionEvent *pNotifyActionEvent);

      /** @brief �B�z�q���T�� */
      void procNotify();

      friend class CActionDispatch;  // ���\CActionDispatch�Ӧs��������private����
      friend class CActionEditorDlg; // ���\�ʧ@�s�边�Ӧs��������
      friend class CUnitObject;

      std::string m_machineName;   // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      std::string m_actionFile;    // �ʧ@�t�άO�ϥέ����ɮ�
      float       m_fCurTime;      // �ثe���ɶ�
      int         m_iCurAction;    // �ثe�ʧ@
      long long   m_uid;           // ���a�B�Ǫ��BNPC���ߤ@�s��
      bool        m_bChangeAction; // �ʧ@�O�_����
      
      std::vector<CActionEvent *>       *m_pEventQueue;   // Action Event Queue
      std::vector<CNotifyActionEvent *> *m_pNotifyQueue;  // Action Notify Queue
      std::vector<CAction *>            *m_pActionVector; // �ʧ@���X
      std::set<int>                     *m_pKeyDownSet;   // �O��������U

      std::set<IDrawWeaponNotifyListener *>  m_drawWeaponNotifyListeners;
      std::set<IPutinWeaponNotifyListener *> m_putinWeaponNotifyListeners;
      std::set<IPlaySoundNotifyListener *>   m_playSoundNotifyListeners;
};

#endif  // #ifndef _CACTIONSYSTEM_H_