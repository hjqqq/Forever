/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IFightEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/20 */
#ifndef _IFIGHTEVENTLISTENER_H_
#define _IFIGHTEVENTLISTENER_H_
#include "Common.h"

class CActionEvent;
class CCastSkillActionEvent;

/** @brief �԰��t�Ψƥ��ť, �i�H�q���ݭn���D������ (�Ω�Server��) */
class IFightEventListener
{
   public:
      /** @brief ��s�԰��t�εo�X���ʧ@�T�� 
        * @param pUnitObject ��
        * @param pActEvent   �ʧ@�T�� */
      virtual void updateFightActionEvent(CUnitObject *pUnitObject, CActionEvent *pActEvent) = 0;

      /** @brief ��s�ϥΧޯध�e�n�]�B��ؼЪ�
        * @param pUnitObject   �� */
      virtual void updateFightTargetPosition(CUnitObject *pUnitObject) = 0;

      /** @brief ��s�ؼЪ����`�᪺�B�z
        * @param pUnitObject   ��
        * @param pTargetObject �ؼЪ� */
      virtual void updateFightTargetDead(CUnitObject *pUnitObject, CUnitObject *pTargetObject) = 0;
};

#endif  // #ifndef _IFIGHTEVENTLISTENER_H_