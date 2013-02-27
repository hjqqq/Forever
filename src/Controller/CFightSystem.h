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
#include "IFightEventListener.h"

class CUnitObject;

/** @brief ���Ѿ԰����y�{�P�s��ިϥ�
  *        �԰��L�{�|����ʧ@�t�� */
class CFightSystem
{
   public:
      CFightSystem();

      void init(std::string machineName, long long uid);
      void useSkill(CSkill *pSkill);
      bool isCastSkill();
      void setUID(long long uid);

      void addFightEventListener(IFightEventListener *pListener);
      void removeFightEventListener(IFightEventListener *pListener);

      /** @brief �޿�ʧ@
        * @param timePass �@��frame�X��
        * @param pSelfObject   �ۤv
        * @param pTargetObject �ؼЪ� */
      void work(float timePass, CUnitObject *pSelfObject, CUnitObject *pTargetObject);

   private:
      void notifyActionEventUpdate(CUnitObject *pSelfObject, CActionEvent *pActEvent);
      void notifyTargetPositionUpdate(CUnitObject *pSelfObject);
      void notifyTargetDeadUpdate(CUnitObject *pSelfObject, CUnitObject *pTargetObject);

      std::string    m_machineName;   // �����W�� (�Ψ��ѧO�O���P����, ex: Client1 / Client2 / Client3 / GameServer1 / GameServer2 / WorldServer1)
      long long      m_uid;           // ���a�B�Ǫ��BNPC���ߤ@�s��
      CSkill        *m_pUseSkill;
      int            m_castSkillID;   // �ثe�I�i�ޯ઺ID
      bool           m_bFightState;

      std::set<IFightEventListener *>  m_fightEventListeners;    // ��ť�԰��t�Ψƥ󪺺�ť�̦C��
};

#endif  // #ifndef _CFIGHTSYSTEM_H_