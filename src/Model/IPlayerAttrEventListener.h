/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerAttrEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/19 */
#ifndef _IPLAYERATTREVENTLISTENER_H_
#define _IPLAYERATTREVENTLISTENER_H_
#include "Common.h"

class CPlayer;

/** @brief ���a�ݩʨƥ��ť, �i�H�q���ݭn���D������ */
class IPlayerAttrEventListener
{
   public:
      /** @brief ��s���a�ݩ� (XP, Money�ܰʮ�)
        * @param pPlayer ��s������ */
      virtual void updatePlayerAttr(CPlayer *pPlayer, unsigned int offsetXP, long long offsetMoney) = 0;
};

#endif  // #ifndef _IPLAYERATTREVENTLISTENER_H_