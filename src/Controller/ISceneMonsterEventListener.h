/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   ISceneMonsterEventListener.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/02/16 */
#ifndef _ISCENEMONSTEREVENTLISTENER_H_
#define _ISCENEMONSTEREVENTLISTENER_H_
#include "Common.h"

class CMonster;

/** @brief �����Ǫ��ƥ��ť, �i�H�q���ݭn���D������ (�Ω�Server��) */
class ISceneMonsterEventListener
{
   public:
      /** @brief ��s�[�Ǫ�
        * @param pMonster �s�[���Ǫ� */
      virtual void updateAddMonster(CMonster *pMonster) = 0;
};

#endif  // #ifndef _ISCENEMONSTEREVENTLISTENER_H_