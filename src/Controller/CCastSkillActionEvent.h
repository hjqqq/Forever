/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CCastSkillActionEvent.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CCASTSKILLACTIONEVENT_H_
#define _CCASTSKILLACTIONEVENT_H_
#include "CActionEvent.h"

// AET_CAST_SKILL�M�ΡA��I�i�ޯ�ɡA�ʧ@�t�η|Ĳ�o�ӧ��ܰʧ@
class CCastSkillActionEvent : public CActionEvent
{
   public:
      CCastSkillActionEvent();

      // CActionEvent
      /* virtual */ void operator=(CActionEvent &actEvent);
      /* virtual */ bool operator==(CActionEvent &actEvent);
      /* virtual */ void clear();

      bool  m_bCastSkill;      // �O�_�I�i�ޯ�
      int   m_iCastSkillID;    // �ޯ�s��
      float m_fCastSkillTime;  // �I�i�ɶ�
};

#endif  // #ifndef _CCASTSKILLACTIONEVENT_H_