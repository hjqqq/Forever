/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CActionDispatch.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/12/22 */
#ifndef _CACTIONDISPATCH_H_
#define _CACTIONDISPATCH_H_
#include "Common.h"
#include "CActionSystem.h"

/** @brief �ʧ@�T�����e */
class CActionDispatch
{
   public:
      /** @brief ���oCActionDispatch���骫��
        * @return CActionDispatch���骫�� */
      static CActionDispatch* getInstance();

      /** @brief ����CActionDispatch���骫�� */
      static void releaseInstance();

      /** @brief �[�J�n����ʧ@�T�����ʧ@�t�Ϊ���
        * @param uid           CUnitObject��uid
        * @param pActionSystem �ʧ@�t�Ϊ��� */
      void addActionSystem(long long uid, CActionSystem *pActionSystem);

      /** @brief �e���Y��uid�ʧ@�T��
        * @param uid      CUnitObject��uid
        * @param actEvent �ʧ@�T�� */
      void sendEvnet(long long uid, CActionEvent &actEvent);

   private:
      CActionDispatch();
      ~CActionDispatch();

      static CActionDispatch *m_pInstance;  // CActionDispatch���骫��

      std::map<long long, CActionSystem*> *m_pEventTable;  // �T����Ӫ�
};

#endif  // #ifndef _CACTIONDISPATCH_H_