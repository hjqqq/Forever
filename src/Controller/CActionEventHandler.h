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
        * @param triggerEvent Ĳ�o�ʧ@�ƥ�
        * @param nextActionID �U�@�Ӱʧ@ */
      void init(CActionEvent &triggerEvent, int nextActionID);

      /** @brief ���o�U�@�Ӱʧ@�s��
        * @return �ʧ@�s�� */
      int getNextActionID();

      /** @brief �ˬdĲ�o���ƥ�O�_�PHandler�۲ŦX
        * @param pEvent       Ĳ�o���ʧ@�ƥ�
        * @param pKeyDownList ������U���C��
        * @return true - �۲ŦX / false - ���ŦX */
      bool check(CActionEvent *pEvent, std::list<int> *pKeyDownList);

   private:
      CActionEvent m_triggerEvent;   // Ĳ�o�T��
      int          m_iNextActionID;  // Ĳ�o��n����Y�Ӱʧ@
};

#endif  // #ifndef _CACTIONEVENTHANDLER_H_