/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionEventHandler.cpp
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/21 */
#include "CActionEventHandler.h"

CActionEventHandler::CActionEventHandler()
{
   m_iNextActionID = 0;
}

CActionEventHandler::~CActionEventHandler()
{
}

void CActionEventHandler::init(CActionEvent &triggerEvent, int nextActionID)
{
   m_triggerEvent  = triggerEvent;
   m_iNextActionID = nextActionID;
}

int CActionEventHandler::getNextActionID()
{
   return m_iNextActionID;
}

bool CActionEventHandler::check(CActionEvent *pEvent, std::list<int> *pKeyDownList)
{
   if(pEvent == NULL)
      return false;

   if(pEvent->m_event == m_triggerEvent.m_event) {
      
      if(pEvent->m_event == AET_KEY) {
         if(pEvent->m_iKeyID == m_triggerEvent.m_iKeyID)
            return true;
         else
            return false;
      }
      else if(pEvent->m_event == AET_KEY_WASD) {
         if((m_triggerEvent.m_iKeyDownID > 0) && (pEvent->m_iKeyDownID == m_triggerEvent.m_iKeyDownID)) {
            // ������U

            // �M����U������O�_�s�b��C��
            std::list<int>::iterator it = pKeyDownList->begin();
            while(it != pKeyDownList->end()) {
               if((*it) == pEvent->m_iKeyDownID)
                  break;

               it++;
            }

            // �䤣�즹���U������
            if(it == pKeyDownList->end()) {
               pKeyDownList->push_back(pEvent->m_iKeyDownID);  // �[�J����
               return true;
            }
            else
               return false;
         }
         else if((m_triggerEvent.m_iKeyUpID > 0) && (pEvent->m_iKeyUpID == m_triggerEvent.m_iKeyUpID)) {
            // �����}

            // �M���}������O�_���e���s�b��C��
            std::list<int>::iterator it = pKeyDownList->begin();
            while(it != pKeyDownList->end()) {
               if((*it) == pEvent->m_iKeyUpID)
                  break;

               it++;
            }

            // ����}����
            if(it != pKeyDownList->end()) {
               pKeyDownList->erase(it);      // �R��������
               
               if(pKeyDownList->size() > 0)
                  return false;   // �C���٦���L���U������, �h�O���ܴ��ʧ@
               else
                  return true;    // �C���A�L������U������, �h�ܴ��ʧ@
            }
            else
               return false;
         }
         else if((m_triggerEvent.m_iKeyUpID > 0) && (m_triggerEvent.m_iKeyUpID == pEvent->m_iKeyDownID)) {
            // �ʱ������䬰KeyUP���A, ���O�{���q�i�Ӫ�����T���O�ʱ����䪺KeyDown���A

            // �M����U������O�_�s�b��C��
            std::list<int>::iterator it = pKeyDownList->begin();
            while(it != pKeyDownList->end()) {
               if((*it) == pEvent->m_iKeyDownID)
                  break;

               it++;
            }

            // �䤣�즹���U������
            if(it == pKeyDownList->end())
               pKeyDownList->push_back(pEvent->m_iKeyDownID);  // �[�J����

            return false;  // �ѩ󤣲ŦX�ʱ����䪬�A, �ҥH���ܴ��ʧ@
         }
         else
            return false;
      }
      else
         return true;
   }
   else
      return false;
}

void CActionEventHandler::write(FILE *pFile)
{
   int version = 0;
	fwrite(&version, sizeof(version), 1, pFile);

   int iEvent = 0;
   switch(m_triggerEvent.m_event) {
      case AET_NULL:
         iEvent = 0;
         break;

      case AET_REACH:
         iEvent = 1;
         break;

      case AET_NOT_REACH:
         iEvent = 2;
         break;

      case AET_KEY:
         iEvent = 3;
         break;

      case AET_KEY_WASD:
         iEvent = 4;
         break;

      case AET_CAST_SKILL:
         iEvent = 5;
         break;
   }
   fwrite(&iEvent, sizeof(iEvent), 1, pFile);

   fwrite(&(m_triggerEvent.m_iKeyID), sizeof(m_triggerEvent.m_iKeyID), 1, pFile);
   fwrite(&(m_triggerEvent.m_iKeyDownID), sizeof(m_triggerEvent.m_iKeyDownID), 1, pFile);
   fwrite(&(m_triggerEvent.m_iKeyUpID), sizeof(m_triggerEvent.m_iKeyUpID), 1, pFile);

   int iCastSkill = 0;
   if(m_triggerEvent.m_bCastSkill == true)
      iCastSkill = 1;
   else
      iCastSkill = 0;
   fwrite(&iCastSkill, sizeof(iCastSkill), 1, pFile);

   fwrite(&(m_triggerEvent.m_iCastSkillID), sizeof(m_triggerEvent.m_iCastSkillID), 1, pFile);
   fwrite(&(m_triggerEvent.m_fCastSkillTime), sizeof(m_triggerEvent.m_fCastSkillTime), 1, pFile);
   fwrite(&m_iNextActionID, sizeof(m_iNextActionID), 1, pFile);
}

void CActionEventHandler::read(FILE *pFile)
{
   int version = 0;
	fread(&version, sizeof(version), 1, pFile);

   int iEvent = 0;
   fread(&iEvent, sizeof(iEvent), 1, pFile);
   switch(iEvent) {
      case 0:
         m_triggerEvent.m_event = AET_NULL;
         break;

      case 1:
         m_triggerEvent.m_event = AET_REACH;
         break;

      case 2:
         m_triggerEvent.m_event = AET_NOT_REACH;
         break;

      case 3:
         m_triggerEvent.m_event = AET_KEY;
         break;

      case 4:
         m_triggerEvent.m_event = AET_KEY_WASD;
         break;

      case 5:
         m_triggerEvent.m_event = AET_CAST_SKILL;
         break;
   }

   fread(&(m_triggerEvent.m_iKeyID), sizeof(m_triggerEvent.m_iKeyID), 1, pFile);
   fread(&(m_triggerEvent.m_iKeyDownID), sizeof(m_triggerEvent.m_iKeyDownID), 1, pFile);
   fread(&(m_triggerEvent.m_iKeyUpID), sizeof(m_triggerEvent.m_iKeyUpID), 1, pFile);

   int iCastSkill = 0;
   fread(&iCastSkill, sizeof(iCastSkill), 1, pFile);
   if(iCastSkill == 0)
      m_triggerEvent.m_bCastSkill = false;
   else if(iCastSkill == 1)
      m_triggerEvent.m_bCastSkill = true;

   fread(&(m_triggerEvent.m_iCastSkillID), sizeof(m_triggerEvent.m_iCastSkillID), 1, pFile);
   fread(&(m_triggerEvent.m_fCastSkillTime), sizeof(m_triggerEvent.m_fCastSkillTime), 1, pFile);
   fread(&m_iNextActionID, sizeof(m_iNextActionID), 1, pFile);
}