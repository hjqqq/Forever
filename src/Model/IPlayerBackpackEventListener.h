/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerBackpackEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IPLAYERBACKPACKEVENTLISTENER_H_
#define _IPLAYERBACKPACKEVENTLISTENER_H_
#include "Common.h"

class CBackpack;

/** @brief ���a�˳ƨƥ��ť, �i�H�q���ݭn���D������ */
class IPlayerBackpackEventListener
{
   public:
      /** @brief ��s���a�I�]
        * @param pPlayer ��s������ */
      virtual void updatePlayerBackpack(CBackpack *pBackpack) = 0;
};

#endif  // #ifndef _IPLAYERBACKPACKEVENTLISTENER_H_