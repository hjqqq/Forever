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

/** @brief �ʧ@�t�� 
  *        �i�Ω󪱮a�B�Ǫ��BNPC */
class CActionSystem
{
   public:
      CActionSystem(long long uid);
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

   private:
      /** @brief �����ʧ@
        * @param newActionID �s�ʧ@�s�� */
      void changeAction(int newActionID);

      /** @brief �H�e�ʧ@�T��
        * @param actEvent �ʧ@�T�� */
      void sendEvent(CActionEvent &actEvent);

      friend class CActionDispatch;  // ���\CActionDispatch�Ӧs��������private����
      friend class CActionEditorDlg; // ���\�ʧ@�s�边�Ӧs��������

      float     m_fCurTime;      // �ثe���ɶ�
      int       m_iCurAction;    // �ثe�ʧ@
      long long m_uid;           // ���a�B�Ǫ��BNPC���ߤ@�s��
      bool      m_bChangeAction; // �ʧ@�O�_����
      
      std::vector<CActionEvent *> *m_pvtEventQueue; // Action Event Queue
      std::vector<CAction *>      *m_pvtActionSet;  // �ʧ@���X
      std::list<int>              *m_pKeyDownList;  // �O��������U
};

#endif  // #ifndef _CACTIONSYSTEM_H_