#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "CSkillTable.h"
#include "CBuffTable.h"
#include <list>

class CUnitObject
{
public:
	CUnitObject(std::string strName, long long uid, char level = 0); //�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ0��)

	long long getUID();	//���o�ߤ@�s��
	std::string getName();	//���o����W�r
	char getLevel();	//���o����

	void addHP(int hp);	//�W�[/���HP
	int getHP();	//���oHP
	int getHPMax();	//���o�̤jHP

	void addMP(int mp);	//�W�[/���MP
	int getMP();	//���oMP
	int getMPMax();	//���o�̤jMP
  
	void setAdvAttr(AdvancedAttribute advAttr);	//�]�w�ݩ�
	AdvancedAttribute getAdvAttr();	//���o�ݩ�
	BasisAttribute getBasAttr();    //���o��¦�ݩ�

    std::list<CBuffTable> getBuff();    //���o���W��Buff��
    void addBuff(unsigned int id);      //�W�[Buff

    std::vector<CSkillTable> getSkill();    //���o�Ƿ|���ޯ��
    bool addSkill(unsigned int id);         //�ǧޯ�

protected:
    std::vector<CSkillTable> m_vSkill;  //�֦����ޯ�

private:
	long long m_uid;	//�ߤ@�s��
	char m_level;	//����
	std::string m_strName;	//�W�r
	BasisAttribute m_basAttr;		//�򥻼ƭ�
	AdvancedAttribute m_advAttr;	//�ݩ�
	ObscureAttribute m_obsAttr;		//���üƭ�
	ComplexAttribute m_comAttr;		//���A�ݩ�
    FloatPrecentAttribute m_preAttr;//�B�I�Ʀʤ����ݩ�
    std::list<CBuffTable> m_lBuff;	//���W��Buff


	int getHPR();   //���o�^�_���ͩR�O�I
	int getMPR();   //���o�^�_���믫�O�I

    void updateBuff(float timepass);    //��s�Ҧ�Buff���ɶ�
    void SkillCoolDown(float timepass);     //��s�Ҧ��ޯ઺�N�o
};

#endif