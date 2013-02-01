/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CKeyActionEvent.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CKEYACTIONEVENT_H_
#define _CKEYACTIONEVENT_H_
#include "CActionEvent.h"

// AET_KEY�M�ΡA����U�Y����ɡA�ʧ@�t�η|Ĳ�o�ӧ��ܰʧ@
class CKeyActionEvent : public CActionEvent
{
   public:
      CKeyActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      int m_iKeyID;  // ����(�ϥ�Virtual key)
};

#endif  // #ifndef _CKEYACTIONEVENT_H_