/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   ISkillEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/21 */
#ifndef _ISKILLEVENTLISTENER_H_
#define _ISKILLEVENTLISTENER_H_
#include "Common.h"

class CUnitObject;
class CSkill;

/** @brief �ޯ�ƥ��ť, �i�H�q���ݭn���D������ */
class ISkillEventListener
{
   public:
      /** @brief �s�W�@�Գ��ޯ�
        * @param pUnitObject ��
        * @param skillID     �s�ޯ� */
      virtual void updateAddSkill(CUnitObject *pUnitObject, int skillID) = 0;

      /** @brief ��s�]�˳����Y�i���i�� 
        * @param pSkill �ޯ� */
      virtual void updateSkillAvailable(CSkill *pSkill) = 0;

      /** @brief ��s�ޯ�N�o�ɶ�
        * @param pSkill �ޯ� */
      virtual void updateSkillCoolDown(CSkill *pSkill) = 0;
};

#endif  // #ifndef _ISKILLEVENTLISTENER_H_