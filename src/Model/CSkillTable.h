#ifndef _CSKILLTABLE_H_
#define _CSKILLTABLE_H_

#include "CSkillInfoLoader.h"
#include "obj_mTable.h"
#include <map>

typedef ObjTable<CSkill*, CSkillInfoLoader> SKILL_INFO;

class CSkillTable:public SKILL_INFO
{
public:
    static void initSkillTable();   //��l
	float getSurplus(); //���o�N�o�ɶ�
	bool getAvailable();    //���o�O�_���˳�
	void create(unsigned int id);   //�]�w�����ӧޯ�
	void afterTime(float timePass); //��s�N�o�ɶ�
	bool isReady(); //�O�_�N�o���F
    bool canLearn(unsigned int lv); //�ثe���ťi���i�H��
    void chackAvailable(std::map<EquipSlot, int> equip);    //��s�諸�˳�
    CSkillTable();
    ~CSkillTable();

private:
	float m_fSurplus;   //�ثe�N�o�ɶ�
	bool m_bAvailable;  //�O�_�˳ƻݭn�˳�
};

#endif