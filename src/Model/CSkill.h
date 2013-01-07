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
	float getSurplus(); //���o�N�o�ɶ�
	bool getAvailable();    //���o�O�_���˳�
	void create(unsigned int id);   //�]�w�����ӧޯ�
	void afterTime(float timePass); //��s�N�o�ɶ�
	bool isReady(); //�O�_�N�o���F
    bool canLearn(unsigned int lv); //�ثe���ťi���i�H��
    void chackAvailable(std::map<EquipSlot, int> equip);    //��s�諸�˳�
    CSkill();
    ~CSkill();

private:
	float m_fSurplus;   //�ثe�N�o�ɶ�
	bool m_bAvailable;  //�O�_�˳ƻݭn�˳�
};

#endif