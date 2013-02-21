/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CNotifyActionEvent.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/29 */
#ifndef _CNOTIFYACTIONEVENT_H_
#define _CNOTIFYACTIONEVENT_H_
#include "CActionEvent.h"

/** @brief �ʧ@�t�γq���~�����󪺰T��
  *        �ʧ@�t�η|�̾ڬY�Ӯɶ��I�ӳq���~���Y�T��
  *        ���S���Ѽƪ��ƥ�ϥ�
  *        Ex: AET_NOTIFY_DRAW_WEAPON,
  *            AET_NOTIFY_PUTIN_WEAPON,
  *            AET_NOTIFY_ATTACK */
class CNotifyActionEvent : public CActionEvent
{
   public:
      CNotifyActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      float m_fBeginTime;      // ���ƥ󪺶}�lĲ�o�ɶ�
      float m_fEndTime;        // ���ƥ󪺵���Ĳ�o�ɶ�
};

#endif  // #ifndef _CNOTIFYACTIONEVENT_H_