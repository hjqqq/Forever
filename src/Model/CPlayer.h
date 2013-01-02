#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CUnitObject.h"
#include "CEquip.h"
#include "CBackPack.h"
#include <map>

class CPlayer:public CUnitObject
{
public:
	CPlayer(std::string strName, long long uid, char level = 1);	//�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ1��)
	void addXP(unsigned int xp);	//�W�[XP unsigned ���a�t��
	unsigned int getXP();			//Ū��XP
	unsigned int getXPMax();		//Ū���̤jXP
	CBackPack getBackPack();		//���o�I�]
	void wearEquip(unsigned int id);//��W id ���˳�
	void shedEquip(EquipSlot grid);	//��U ����˳��� �˳�
	std::map<EquipSlot, int> getEquip();	//���o�˳�map�}�C
	int getEquip(EquipSlot equip);	//���o���@��˳�

private:
	unsigned int m_xp;	//�g���
	unsigned int m_xpMax;	//�̤j�g���
	char m_levelMax;	//�̰����� �w�]50
	std::map<EquipSlot, int> m_mEquip;	//�˳���
	CBackPack m_backPack;   //�I�]

	void upDateEquipAttr(); //��s�˳Ƴy���������ݩ�
	void wearToEquipSlot(EquipSlot es, unsigned int id);    //���˳���W
};

#endif