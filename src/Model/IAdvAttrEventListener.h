/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IAdvAttrEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IADVATTREVENTLISTENER_H_
#define _IADVATTREVENTLISTENER_H_
#include "Common.h"

class CUnitObject;

/** @brief AdvancedAttribute(�i���ݩ�)�ƥ��ť, �i�H�q���ݭn���D������ */
class IAdvAttrEventListener
{
   public:
      /** @brief ��s�i���ݩ� 
        * @param pUnitObject ��s������ */
      virtual void updateAdvAttr(CUnitObject *pUnitObject) = 0;
};

#endif  // #ifndef _IADVATTREVENTLISTENER_H_