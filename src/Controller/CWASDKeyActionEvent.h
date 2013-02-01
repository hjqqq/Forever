/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CWASDKeyActionEvent.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CWASDKEYACTIONEVENT_H_
#define _CWASDKEYACTIONEVENT_H_
#include "CActionEvent.h"

// AET_KEY_WASD�M�ΡA����U/��}�Y����ɡA�ʧ@�t�η|Ĳ�o�ӧ��ܰʧ@
class CWASDKeyActionEvent : public CActionEvent
{
   public:
      CWASDKeyActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      int m_iKeyDownID;  // ���U����(�ϥ�Virtual key)
      int m_iKeyUpID;    // ��}����(�ϥ�Virtual key)
};

#endif  // #ifndef _CWASDKEYACTIONEVENT_H_