#ifndef _CBASEPACKET_H_
#define _CBASEPACKET_H_
#include "Common.h"

enum {
   PACKET_FIRST_LOGIN, PACKET_PASSWORD_GW, PACKET_PLAYER_DATA_WG, PACKET_PLAYER_INIT, // �n�J�y�{
   PACKET_PLAYER_DATA,            // ���a���
   PACKET_TARGET_POS,             // �ؼЦ�m
   PACKET_MONSTER_DATA,           // �Ǫ����
   PACKET_TARGET_OBJECT,          // �ؼЪ�
   PACKET_ACTION_EVENT,           // �ʧ@�t�ΰT��
   PACKET_USE_SKILL,              // �ϥΧޯ�
   PACKET_USE_ITEM,               // �ϥΪ��~
   PACKET_BACKPACK_DATA,          // �I�]���
   PACKET_EQUIP_DATA,             // �˳Ƹ��
   PACKET_ADVATTR_DATA,           // �@�Գ�쪺�i���ݩ� (�]�tHP, MP)
   PACKET_ADD_SKILL,              // �ǲߧޯ�
   PACKET_CAN_USE_SKILL,          // �O�_����ϥΧޯ�
   PACKET_CANCEL_USESKILL,        // �����ϥΧޯ�
   PACKET_DEAD,                   // ���`
   PACKET_PLAYER_DEAD_RESET,      // ���a���`����
   PACKET_KEYBOARD_POS,           // ���䲾�ʦ�m
   PACKET_NPC_DATA,
   PACKET_BUY_ITEM,
   PACKET_MONEY,
   PACKET_XP,
   PACKET_SELL_ITEM,
   PACKET_KEY_ACTION_EVENT,
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