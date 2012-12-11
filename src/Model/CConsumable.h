#ifndef _CCONSUMABLE_H_
#define _CCONSUMABLE_H_

#include "CItem.h"

class CConsumable:public CItem	//�ӧ��ʪ��~
{
public:
	std::wstring getDesc();
	virtual void read(FILE* pFile);
	virtual void write(FILE* pFile);
	void initWeapon(std::wstring name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					std::wstring desc, EdibleEffectType effect, int much);


private:
	std::wstring m_strDesc;		//���~�y�z
	EdibleEffectType m_effect;	//�ĪG����
	int m_iMuch;				//�v�T�ƭ�
};


#endif