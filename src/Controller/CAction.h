/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CAction.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#ifndef _CACTION_H_
#define _CACTION_H_
#include "CActionEventHandler.h"

typedef struct tagACTION {
   int         iID;            // �ʧ@�s��
   std::string name;           // �ʧ@�W��
   float       fTime;          // �ʧ@�ɶ�
   std::string animationName;  // �ʵe�W��
   int         iNextActID;     // �ʧ@������U�@�Ӱʧ@
   bool        bMove;          // �O�_�i����
} ACTION_DATA;

/** @brief �ʧ@
  *        ���a�ʧ@  ():Event
  *          Idle�ʧ@->(�y�Ч��)->�]�B�ʧ@
  *          Idle�ʧ@->(�ޥX�Z���ֱ���)->�԰����A�ʧ@
  *          Idle�ʧ@->(�Q�Ǫ���)->�԰����A�ʧ@
  *          Idle�ʧ@->(�Z���L��,�I�i�ޯ�)->�԰����A�ʧ@
  *          Idle�ʧ@->(�ޯ�d��,�I�i�ޯ�)->�԰����A�ʧ@
  *
  *          �԰����A�ʧ@->(�ޯ�d��,�I�i�ޯ�)->�ޯ�ʧ@->���q�����ʧ@->�԰����A�ʧ@
  *          �԰����A�ʧ@->(�y�Ч��)->�԰����A���]�B�ʧ@
  *          �԰����A�ʧ@->(�D�԰����A1������)->Idle�ʧ@
  *          �԰����A�ʧ@->(�D�԰����A���Z���ֱ���)->Idle�ʧ@
  *
  *          �]�B�ʧ@->(�y�еL���)->Idle�ʧ@
  *          �]�B�ʧ@->(�Q�Ǫ���)->�԰����A�ʧ@
  *
  *          �԰����A���]�B�ʧ@->(�y�еL���)->�԰����A�ʧ@
  *          �԰����A���]�B�ʧ@->(�Q�Ǫ���)->�԰����A�ʧ@
  *          �԰����A���]�B�ʧ@->(�D�԰����A1������)->�]�B�ʧ@ */
class CAction
{
   public:
      CAction();
      ~CAction();

      /** @brief ��l��
        * @param data �ʧ@��� */
      void init(ACTION_DATA &data);

      /** @brief �[�J�v�T���ƥ�
        * @param pHandler �ʧ@�ƥ� */
      void addEventHandler(CActionEventHandler *pHandler);

      /** @brief ���o�ʧ@�s��
        * @return �ʧ@�s�� */
      int getID();

      /** @brief �ʧ@��s
        * @param fPreTime    �W�@���ɶ�
        * @param fCurTime    �ثe�ɶ�
        * @param pEvent      �ʧ@�ƥ�
        * @param pKeyDownSet ������U���C��
        * @return �U�@�Ӱʧ@�s�� (< 0 ��ܵL�ʧ@) */
      int work(float fPreTime, float fCurTime, CActionEvent *pEvent, std::set<int> *pKeyDownSet);

      /** @brief ���o�ʵe�W��
        * @return �ʵe�W�� */
      std::string getAnimationName();

      /** @brief �O�_�i����
        * @return true - �i���� / false - ���i���� */
      bool isMove();

      /** @brief ���o�ʧ@�W��
        * @return �ʧ@�W�� */
      std::string getName();

      void setUID(long long uid);

      void setMachineName(std::string machineName);

      /** @brief ���o����U�@�Ӱʧ@ID
        * @return  0    ���Ƽ���
        *         -1    �u����@��
        *         > 0   �U�@�Ӱʧ@ID */
      int getNextActionID();

      /** @brief ���o�Ӱʧ@���ɶ����� */
      float getActionTimeLength();

      /** @brief �s��
        * @param pFile �ɮ� */
      void write(FILE *pFile);

      /** @brief Ū��
        * @param pFile �ɮ� */
      void read(FILE *pFile);

   private:
      friend class CActionEditorDlg; // ���\�ʧ@�s�边�Ӧs��������

      std::string m_machineName;    // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      int         m_iID;            // �ʧ@�s��
      std::string m_name;           // �ʧ@�W��
      float       m_fTime;          // �ʧ@�ɶ�
      std::string m_animationName;  // �ʵe�W��
      int         m_iNextActID;     // �ʧ@������U�@�Ӱʧ@
      bool        m_bMove;          // �O�_�i����
      long long   m_uid;            // ���a�B�Ǫ��BNPC���ߤ@�s��

      std::vector<CActionEventHandler *> m_eventHandlerSet;  // �Ӱʧ@�|�����Ǩƥ�v�T�ӧ󴫰ʧ@
};

#endif  // #ifndef _CACTION_H_