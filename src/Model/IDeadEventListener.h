/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IDeadEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/21 */
#ifndef _IDEADEVENTLISTENER_H_
#define _IDEADEVENTLISTENER_H_
#include "Common.h"

class CUnitObject;

/** @brief �Ǫ�/NPC/���a���`�ƥ��ť, �i�H�q���ݭn���D������ */
class IDeadEventListener
{
   public:
      /** @brief ��s���Y���󦺤` 
        * @param uid �� */
      virtual void updateDead(long long uid) = 0;
};

#endif  // #ifndef _IDEADEVENTLISTENER_H_