/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CPacketSellItem.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/17 */
#ifndef _CPACKETSELLITEM_H_
#define _CPACKETSELLITEM_H_
#include "CBasePacket.h"
#include "CUnitObject.h"
#include "CItem.h"

class CPacketSellItem : public CBasePacket
{
   public:
      CPacketSellItem() : CBasePacket(PACKET_SELL_ITEM)
      {
      }

      long long getUID();
      int getBackpackGrid();
      int getItemID();

      void pack(CUnitObject *pUnitObject, int backpackGrid, CItem *pItem);

   private:
      long long m_uid;      // ��
      int m_backpackGrid;   // �I�]���@�檺���~
      int m_itemID;         // ���Ӫ��~
};

#endif  // #ifndef _CPACKETUSESKILL_H_