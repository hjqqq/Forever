/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IModelEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/16 */
#ifndef _IMODELEVENTLISTENER_H_
#define _IMODELEVENTLISTENER_H_
#include "Common.h"

class CUnitObject;
class CSkill;
typedef struct tagHOTKEYITEM HotKeyItem;

/** @brief Model�ƥ��ť, �i�H�q���ݭn���D������ */
class IModelEventListener
{
   public:
      /** @brief ��s�i���ݩ� 
        * @param pUnitObject ��s������ */
      virtual void updateAdvAttr(CUnitObject *pUnitObject) = 0;

      /** @brief ��s�I�]
        * @param pUnitObject ��s������ */
      virtual void updateBackpack(CUnitObject *pUnitObject) = 0;

      /** @brief ��s�ޯ�
        * @param pUnitObject ��s������ */
      virtual void updateSkill(CUnitObject *pUnitObject) = 0;

      /** @brief ��s�ֱ��䶵��
        * @param field       �������ֱ���
        * @param pHotKeyItem ��s������ */
      virtual void updateHotKeyItem(int field, HotKeyItem *pHotKeyItem) = 0;

      /** @brief ��s�ޯ�N�o�ɶ�
        * @param pSkill �ޯ� */
      virtual void updateCoolDown(CSkill *pSkill) = 0;
};

#endif  // #ifndef _IMODELEVENTLISTENER_H_