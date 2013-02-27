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
#include "CUnitObject.h"
#include "CPlayer.h"
#include "CMonster.h"

CFightSystem::CFightSystem()
{
   m_pUseSkill = NULL;
   m_castSkillID = -1;
   m_bFightState = false;
}

void CFightSystem::init(std::string machineName, long long uid)
{
   m_machineName = machineName;
   m_uid = uid;
}

void CFightSystem::useSkill(CSkill *pSkill)
{
   if(pSkill != NULL) {
      m_pUseSkill = pSkill;
      m_castSkillID = pSkill->getID();
      m_bFightState = true;
   }
   else {
      m_pUseSkill = NULL;
      m_castSkillID = -1;
      m_bFightState = false;
   }
}

bool CFightSystem::isCastSkill()
{
   return m_bFightState;
}

void CFightSystem::setUID(long long uid)
{
   m_uid = uid;
}

void CFightSystem::addFightEventListener(IFightEventListener *pListener)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.find(pListener);
   if(it == m_fightEventListeners.end())
      m_fightEventListeners.insert(pListener);
}

void CFightSystem::removeFightEventListener(IFightEventListener *pListener)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.find(pListener);
   if(it != m_fightEventListeners.end())
      m_fightEventListeners.erase(it);
}

void CFightSystem::work(float timePass, CUnitObject *pSelfObject, CUnitObject *pTargetObject)
{
   if(m_bFightState == false)
      return;

   if(m_pUseSkill != NULL) {
      if(pSelfObject->canUseSkill(m_pUseSkill->getID()) == true) {
         CAction *pSelfCurAction = pSelfObject->getCurAction();

         if(pSelfCurAction->getID() == ACTION_IDLE) {  // ����

            // �o�e�I�i�ޯ�T�������ʧ@ (����->�ޥX�Z��->�԰����A)
            CCastSkillActionEvent actEvent;
            actEvent.m_event = AET_CAST_SKILL;
            CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

            /*CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
            if(pPlayer != NULL)
               notifyActionEventUpdate(pSelfObject, &actEvent);*/
         }
         else if(pSelfCurAction->getID() == ACTION_RUN) {  // �]�B

            CActionEvent actEvent;
            actEvent.m_event = AET_REACH;
            CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

            /*CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
            if(pPlayer != NULL)
               notifyActionEventUpdate(pSelfObject, &actEvent);*/
         }
         else if(pSelfCurAction->getID() == ACTION_FIGHT) {  // �԰����A
            // �P�_�Z���A�Z���ӻ��n�����]�B�ʧ@�B�H���n���� (�u�����a�i�ϥΦ��\��)
            if(pTargetObject != NULL) {
               CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
               if(pPlayer != NULL) {
                  float distance = getDistance(pSelfObject->getPosition().fX, pSelfObject->getPosition().fY,
                                               pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
                  CSkillInfo *pUseSkillInfo = m_pUseSkill->getInfo();
                  if(distance > pUseSkillInfo->getCastRange()) {

                     //size_t idx = m_machineName.find("Server");
                     //if(idx != std::string::npos) {
#ifdef _GAMEENGINE_3D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
#elif _GAMEENGINE_2D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY, true);
#endif
                        CActionEvent actEvent;
                        actEvent.m_event = AET_NOT_REACH;
                        CActionDispatch::getInstance()->sendEvnet(pSelfObject->getMachineName(), pSelfObject->getUID(), actEvent);

                        //notifyTargetPositionUpdate(pSelfObject);
                     //}

                     return;
                  }
               }
            }

            // ����ؼ�
            CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
            if(pPlayer != NULL) {
               float targetDirection = pTargetObject->getDirection();
               float selfNewDirection = targetDirection + 3.1415926f;
               selfNewDirection = fmod(selfNewDirection, (2.0f * -3.1415926f));
               pSelfObject->setDirection(selfNewDirection);
            }

            // �P�_�I�k�ɶ��A�O�_�n�����u�۰ʧ@

            // �o�e�I�i�ޯ�T�������ʧ@
            CCastSkillActionEvent actEvent;
            actEvent.m_event = AET_CAST_SKILL;
            actEvent.m_bCastSkill = true;
            actEvent.m_iCastSkillID = m_pUseSkill->getID();
            actEvent.m_fCastSkillTime = m_pUseSkill->getInfo()->getCastTime();
            CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

            // �P�_���L�s��ޡA�����ܭn�q��UI

            m_pUseSkill = NULL;
         }
         else if(pSelfCurAction->getID() == ACTION_FIGHT_RUN) {  // �԰����A�]�B
            //size_t idx = m_machineName.find("Server");
            //if(idx != std::string::npos) {
               // �P�_�Z���A�Z���ӻ��~��]�B�ʧ@�B�H���n���� (�u�����a�i�ϥΦ��\��)
               if(pTargetObject != NULL) {
                  CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
                  if(pPlayer != NULL) {
                     float distance = getDistance(pSelfObject->getPosition().fX, pSelfObject->getPosition().fY,
                                                  pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
                     CSkillInfo *pUseSkillInfo = m_pUseSkill->getInfo();
                     if(distance > pUseSkillInfo->getCastRange()) {
#ifdef _GAMEENGINE_3D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY);
#elif _GAMEENGINE_2D_
                        pSelfObject->setTargetPosition(pTargetObject->getPosition().fX, pTargetObject->getPosition().fY, true);
#endif
                        CActionEvent actEvent;
                        actEvent.m_event = AET_NOT_REACH;
                        CActionDispatch::getInstance()->sendEvnet(pSelfObject->getMachineName(), pSelfObject->getUID(), actEvent);

                        //notifyTargetPositionUpdate(pSelfObject);

                        return;
                     }
                  }
               }

               CActionEvent actEvent;
               actEvent.m_event = AET_REACH;
               CActionDispatch::getInstance()->sendEvnet(m_machineName, m_uid, actEvent);

               /*CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
               if(pPlayer != NULL)
                  notifyActionEventUpdate(pSelfObject, &actEvent);*/
            //}
         }
      }
   }
   else {
      CPlayer *pPlayer = dynamic_cast<CPlayer *>(pSelfObject);
      if(pPlayer != NULL) {
         CAction *pSelfCurAction = pSelfObject->getCurAction();
         if((pSelfObject->isChangeAction() == true) && pSelfCurAction->getID() == ACTION_FIGHT) {  // �԰����A
            if(pTargetObject == NULL)
               return;

            if(pTargetObject->getHP() <= 0) {
               m_bFightState = false;
               notifyTargetDeadUpdate(pSelfObject, pTargetObject);
               return;
            }

            m_pUseSkill = pSelfObject->getSkill(0);
            m_castSkillID = m_pUseSkill->getID();
         }
      }
      else
         m_bFightState = false;
   }
}

void CFightSystem::notifyActionEventUpdate(CUnitObject *pSelfObject, CActionEvent *pActEvent)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.begin();
   while(it != m_fightEventListeners.end()) {
      (*it)->updateFightActionEvent(pSelfObject, pActEvent);
      ++it;
   }
}

void CFightSystem::notifyTargetPositionUpdate(CUnitObject *pSelfObject)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.begin();
   while(it != m_fightEventListeners.end()) {
      (*it)->updateFightTargetPosition(pSelfObject);
      ++it;
   }
}

void CFightSystem::notifyTargetDeadUpdate(CUnitObject *pSelfObject, CUnitObject *pTargetObject)
{
   std::set<IFightEventListener *>::iterator it = m_fightEventListeners.begin();
   while(it != m_fightEventListeners.end()) {
      (*it)->updateFightTargetDead(pSelfObject, pTargetObject);
      ++it;
   }
}