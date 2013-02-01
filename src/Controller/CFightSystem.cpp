/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CFightSystem.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#include "CFightSystem.h"
#include "CAction.h"
#include "CActionDispatch.h"
#include "CCastSkillActionEvent.h"

CFightSystem::CFightSystem(long long uid) : m_uid(uid),
                                            m_pUseSkill(NULL)
{
}

void CFightSystem::useSkill(CSkill *pSkill)
{
   m_pUseSkill = pSkill;
}

void CFightSystem::work(float timePass, CUnitObject *pSelfObject, CUnitObject *pTargetObject)
{
   if(m_pUseSkill != NULL) {
      if(pSelfObject->canUseSkill(m_pUseSkill->getID()) == true) {
         CAction *pSelfCurAction = pSelfObject->getCurAction();

         if(pSelfCurAction->getID() == ACTION_IDLE) {  // ����

            // �o�e�I�i�ޯ�T�������ʧ@ (����->�ޥX�Z��->�԰����A)
            CCastSkillActionEvent actEvent;
            actEvent.m_event = AET_CAST_SKILL;
            CActionDispatch::getInstance()->sendEvnet(m_uid, actEvent);
         }
         else if(pSelfCurAction->getID() == ACTION_RUN) {  // �]�B

            
         }
         else if(pSelfCurAction->getID() == ACTION_FIGHT) {  // �԰����A
            // �P�_�Z���A�Z���ӻ��n�����]�B�ʧ@�B�H���n����

            // �P�_�I�k�ɶ��A�O�_�n�����u�۰ʧ@

            // �o�e�I�i�ޯ�T�������ʧ@
            CCastSkillActionEvent actEvent;
            actEvent.m_event = AET_CAST_SKILL;
            actEvent.m_bCastSkill = true;
            actEvent.m_iCastSkillID = m_pUseSkill->getID();
            //actEvent.m_fCastSkillTime = m_pUseSkill->getInfo()->getCastTime();
            CActionDispatch::getInstance()->sendEvnet(m_uid, actEvent);

            // ����p��

            // �P�_���L�s��ޡA�����ܭn�q��UI

            m_pUseSkill = NULL;
         }
      }
   }
}