/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEventHandler.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#ifndef _CACTIONEVENTHANDLER_H_
#define _CACTIONEVENTHANDLER_H_
#include "Common.h"
#include "CActionEvent.h"

/** @brief Ĳ�o�ʧ@���ܪ��ƥ� */
class CActionEventHandler
{
   public:
      CActionEventHandler();
      ~CActionEventHandler();

      /** @brief ��l��
        * @param pTriggerEvent Ĳ�o�ʧ@�ƥ�
        * @param nextActionID  �U�@�Ӱʧ@ */
      void init(CActionEvent *pTriggerEvent, int nextActionID);

      /** @brief ���o�U�@�Ӱʧ@�s��
        * @return �ʧ@�s�� */
      int getNextActionID();

      /** @brief �ˬdĲ�o���ƥ�O�_�PHandler�۲ŦX
        * @param fPreTime    �W�@���ɶ�
        * @param fCurTime    �ثe�ɶ�
        * @param pEvent      Ĳ�o���ʧ@�ƥ�
        * @param pKeyDownSet ������U���C��
        * @return true  - �۲ŦX���ʧ@
        *         false - ���ŦX�����ʧ@ */
      bool check(float fPreTime, float fCurTime, CActionEvent *pEvent, std::set<int> *pKeyDownSet);

      void setUID(long long uid);

      void setMachineName(std::string machineName);

      /** @brief �s��
        * @param pFile �ɮ� */
      void write(FILE *pFile);

      /** @brief Ū��
        * @param pFile �ɮ� */
      void read(FILE *pFile);

   private:
      friend class CActionEditorDlg;  // ���\�ʧ@�s�边�Ӧs��������

      std::string   m_machineName;    // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      CActionEvent *m_pTriggerEvent;  // Ĳ�o�T��
      int           m_iNextActionID;  // Ĳ�o��n����Y�Ӱʧ@
      long long     m_uid;            // ���a�B�Ǫ��BNPC���ߤ@�s��
};

#endif  // #ifndef _CACTIONEVENTHANDLER_H_