/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IPlayerHotKeyEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/21 */
#ifndef _IPLAYERHOTKEYEVENTLISTENER_H_
#define _IPLAYERHOTKEYEVENTLISTENER_H_
#include "Common.h"

typedef struct tagHOTKEYITEM HotKeyItem;

/** @brief �ֱ���ƥ��ť, �i�H�q���ݭn���D������ */
class IPlayerHotKeyEventListener
{
   public:
      /** @brief ��s���a���ֱ���
        * @param pHotKeyItem ��s���ֱ��� */
      virtual void updatePlayerHotKey(HotKeyItem *pHotKeyItem) = 0;
};

#endif  // #ifndef _IPLAYERHOTKEYEVENTLISTENER_H_