#ifndef _CSKILL_H_
#define _CSKILL_H_

#include "Common.h"
#include "CSkillInfoLoader.h"
#include "obj_mTable.h"
#include "ISkillEventListener.h"

typedef ObjTable<CSkillInfo*, CSkillInfoLoader> SKILL_INFO;

class CSkill:public SKILL_INFO
{
   public:
      static void initSkill();   //��l

      CSkill();
      ~CSkill();

      float getSurplus(); //���o�N�o�ɶ�
      bool getAvailable();    //���o�O�_���˳�
      void create(unsigned int skillID);   //�]�w�����ӧޯ�
      void startCoolDown();  // �}�l�p��N�o�ɶ� Add by Darren Chen on 2013/01/16
      void updateCoolDown(float timePass); //��s�N�o�ɶ�  Modify by Darren Chen on 2013/01/13
      bool isReady(); //�O�_�N�o���F
      bool canLearn(unsigned int lv); //�ثe���ťi���i�H��
      void checkAvailable(std::map<EquipSlot, int> equip);    //��s�諸�˳�

      // Add by Darren Chen on 2013/01/21 {
      /** @brief �[�J��ť�ޯ�ƥ󪺪���
        * @param pListener ��ť�� */
      void addSkillEventListener(ISkillEventListener *pListener);

      /** @brief ������ť�ޯ�ƥ󪺪���
        * @param pListener ��ť�� */
      void removeSkillEventListener(ISkillEventListener *pListener);
      // } Add by Darren Chen on 2013/01/21

   private:
	   float m_fSurplus;   //�ثe�N�o�ɶ�
	   bool m_bAvailable;  //�O�_�˳ƻݭn�˳�

      // Add by Darren Chen on 2013/01/21 {
      /** @brief �q���ޯ�N�o�ɶ�����s */
      void notifySkillCoolDownUpdate();

      /** @brief �q���ޯ�i���i�Φ���s */
      void notifySkillAvailableUpdate();

      std::set<ISkillEventListener *> m_skillEventListeners;   // ��ť�ޯ���ܪ���ť�̦C��
      // } Add by Darren Chen on 2013/01/21
};

#endif