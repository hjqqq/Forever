#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CUnitObject.h"
#include "CItem.h"
#include "CEquip.h"
#include <map>

class CPlayer:public CUnitObject
{
public:
	CPlayer(std::wstring strName,char level = 1);	//�إߨ��� �ǤJ�W�r�B����(�w�]�إ߫ᬰ1��)
	void addXP(unsigned int xp);	//�W�[XP unsigned ���a�t��
	unsigned int getXP();			//Ū��XP
	unsigned int getXPMax();		//Ū���̤jXP

private:
	unsigned int m_xp;	//�g���
	unsigned int m_xpMax;	//�̤j�g���
	char m_levelMax;	//�̰����� �w�]50
	std::map<EquipSlot ,CEquip*> m_mpEquip;	//
};

#endif