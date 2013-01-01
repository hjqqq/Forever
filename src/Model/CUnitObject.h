#ifndef _CUNITOBJECT_H_
#define _CUNITOBJECT_H_

#include "Common.h"
#include "AttributeSet.h"

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
  
	void addHPR(int hpr);

	void addMPR(int mpr);
  
	void setAdvAttr(AdvancedAttribute advAttr);	//�]�w�ݩ�
	AdvancedAttribute getAdvAttr();	//���o�ݩ�
	BasisAttribute getBasAttr();

protected:

private:
	long long m_uid;	//�ߤ@�s��
	char m_level;	//����
	std::string m_strName;	//�W�r
	BasisAttribute m_basAttr;		//�򥻼ƭ�
	AdvancedAttribute m_advAttr;	//�ݩ�
	ObscureAttribute m_obsAttr;		//���üƭ�

};

#endif