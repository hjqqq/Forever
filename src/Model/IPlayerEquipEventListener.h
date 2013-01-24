/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerEquipEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IPLAYEREQUIPEVENTLISTENER_H_
#define _IPLAYEREQUIPEVENTLISTENER_H_
#include "Common.h"

class CPlayer;

/** @brief ���a�˳ƨƥ��ť, �i�H�q���ݭn���D������ */
class IPlayerEquipEventListener
{
   public:
      /** @brief ��s���a�˳�
        * @param pPlayer ��s������ */
      virtual void updatePlayerEquip(CPlayer *pPlayer) = 0;
};

#endif  // #ifndef _IPLAYEREQUIPEVENTLISTENER_H_