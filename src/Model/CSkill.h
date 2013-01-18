#ifndef _CSKILL_H_
#define _CSKILL_H_

#include "CSkillInfoLoader.h"
#include "obj_mTable.h"
#include <map>

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
      bool updateCoolDown(float timePass); //��s�N�o�ɶ�  Modify by Darren Chen on 2013/01/13
      bool isReady(); //�O�_�N�o���F
      bool canLearn(unsigned int lv); //�ثe���ťi���i�H��
      void checkAvailable(std::map<EquipSlot, int> equip);    //��s�諸�˳�

   private:
	   float m_fSurplus;   //�ثe�N�o�ɶ�
	   bool m_bAvailable;  //�O�_�˳ƻݭn�˳�
};

#endif