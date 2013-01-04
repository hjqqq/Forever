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