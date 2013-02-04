/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   CFightSystem.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2013/01/28 */
#ifndef _CFIGHTSYSTEM_H_
#define _CFIGHTSYSTEM_H_
#include "CSkill.h"

class CUnitObject;

/** @brief ���Ѿ԰����y�{�P�s��ިϥ�
  *        �԰��L�{�|����ʧ@�t�� */
class CFightSystem
{
   public:
      CFightSystem(long long uid);

      void useSkill(CSkill *pSkill);
      bool isCastSkill();

      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X��
        * @param pSelfObject   �ۤv
        * @param pTargetObject �ؼЪ� */
      void work(float timePass, CUnitObject *pSelfObject, CUnitObject *pTargetObject);

   private:
      long long      m_uid;           // ���a�B�Ǫ��BNPC���ߤ@�s��
      CSkill        *m_pUseSkill;
};

#endif  // #ifndef _CFIGHTSYSTEM_H_