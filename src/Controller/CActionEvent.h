/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEvent.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/27 */
#ifndef _CACTIONEVENT_H_
#define _CACTIONEVENT_H_
#include "Common.h"

/** @brief �ʧ@�ƥ�
  *        ���ƥ�S���Ѽƪ��ϥ� 
  *        ex: AET_REACH, AET_NOT_REACH */
class CActionEvent
{
   public:
      CActionEvent();

      /** @brief �������
        * @param actEvent CActionEvent���� */
      virtual void operator=(CActionEvent &actEvent);

      /** @brief ����P�_
        * @param actEvent CActionEvent���� */
      virtual bool operator==(CActionEvent &actEvent);

      /** @brief �M����� */
      virtual void clear();

      ACTION_EVENT_TYPE m_event;       // �ʧ@�ƥ�
};

#endif  // #ifndef _CACTIONEVENT_H_