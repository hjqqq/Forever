#ifndef _CBASEPACKET_H_
#define _CBASEPACKET_H_
#include "Common.h"

enum {
   PACKET_FIRST_LOGIN, PACKET_PASSWORD_GW, PACKET_PLAYER_DATA_WG, PACKET_PLAYER_INIT, // 登入流程
   PACKET_PLAYER_DATA,            // 玩家資料
   PACKET_TARGET_POS,             // 目標位置
   PACKET_MONSTER_DATA,           // 怪物資料
   PACKET_TARGET_OBJECT,          // 目標物
   PACKET_ACTION_EVENT,           // 動作系統訊息
   PACKET_USE_SKILL,              // 使用技能
   PACKET_USE_ITEM,               // 使用物品
   PACKET_BACKPACK_DATA,          // 背包資料
   PACKET_EQUIP_DATA,             // 裝備資料
   PACKET_ADVATTR_DATA,           // 作戰單位的進階屬性 (包含HP, MP)
   PACKET_ADD_SKILL,              // 學習技能
   PACKET_CAN_USE_SKILL,          // 是否能夠使用技能
   PACKET_CANCEL_USESKILL,        // 取消使用技能
   //PACKET_CASTSKILL_ACTIONEVENT,  // 施展技能動作訊息
	PACKET_NPC_DATA,
};

class CBasePacket
{
   public:
      int m_id;

      CBasePacket(int id) {
         m_id = id;
      }
};

#endif  // #ifndef _CBASEPACKET_H_