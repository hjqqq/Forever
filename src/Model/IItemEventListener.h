/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   IItemEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/21 */
#ifndef _IITEMEVENTLISTENER_H_
#define _IITEMEVENTLISTENER_H_
#include "Common.h"

class CItem;

/** @brief ���~��ƥ��ť, �i�H�q���ݭn���D������ */
class IItemEventListener
{
   public:
      /** @brief ��s���~����
        * @param pItem ��s�����~�� */
      virtual void updateItemData(CItem *pItem) = 0;
};

#endif  // #ifndef _IITEMEVENTLISTENER_H_