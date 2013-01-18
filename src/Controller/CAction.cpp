/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CAction.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/20 */
#include "CAction.h"
#include "CSkill.h"

CAction::CAction() : m_iID(0),
                     m_fTime(0.0f),
                     m_iNextActID(-1),
                     m_bMove(false)
{
   m_pvtEventHandlerSet = new std::vector<CActionEventHandler *>();
}

CAction::~CAction()
{
   std::vector<CActionEventHandler *>::iterator it = m_pvtEventHandlerSet->begin();
   while(it != m_pvtEventHandlerSet->end()) {
      delete (*it);
      it++;
   }
   m_pvtEventHandlerSet->clear();
   delete m_pvtEventHandlerSet;
   m_pvtEventHandlerSet = NULL;
}

void CAction::init(ACTION_DATA &data)
{
   m_iID           = data.iID;
   m_name          = data.name;
   m_fTime         = data.fTime;
   m_animationName = data.animationName;
   m_iNextActID    = data.iNextActID;
   m_bMove         = data.bMove;
}

void CAction::addEventHandler(CActionEventHandler *pHandler)
{
   m_pvtEventHandlerSet->push_back(pHandler);
}

int CAction::getID()
{
   return m_iID;
}

int CAction::work(float fCurTime, CActionEvent *pEvent, std::list<int> *pKeyDownList)
{
   if(fCurTime > m_fTime) {
      // �ʧ@����, ���U�@�Ӱʧ@
      return m_iNextActID;
   }
   else {
      // �ˬd���v�T���ƥ󦳨S���QĲ�o, ���QĲ�o�N�ݭn���۹������ʧ@
      std::vector<CActionEventHandler *>::iterator it = m_pvtEventHandlerSet->begin();
      while(it != m_pvtEventHandlerSet->end()) {
         if((*it)->check(pEvent, pKeyDownList) == true) {
            int nextActionID = (*it)->getNextActionID();
            
            // �P�_�n�I�i���ӧޯ�ʧ@
            if((m_iID == 4) && (pEvent->m_bCastSkill == true)) {
               CSkillInfo *pSkillInfo = CSkill::getInfo(pEvent->m_iCastSkillID);
               if(pSkillInfo != NULL) {
                  if(pEvent->m_fCastSkillTime == 0)  // �ߧY�I�i, �L�u�۰ʧ@
                     nextActionID = pSkillInfo->getActionID();
                  else {
                     // ���u�۰ʧ@
                     // Todo: �٨S��
                  }
               }
            }

            return nextActionID;
         }

         it++;
      }

      return -1;  // �ʧ@�٨S���񵲧�
   }
}

std::string CAction::getAnimationName()
{
   return m_animationName;
}

bool CAction::isMove()
{
   return m_bMove;
}

std::string CAction::getName()
{
   return m_name;
}