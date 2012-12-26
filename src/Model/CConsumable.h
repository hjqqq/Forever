#ifndef _CCONSUMABLE_H_
#define _CCONSUMABLE_H_

#include "CItem.h"

class CConsumable:public CItem	//�ӧ��ʪ��~
{
public:
	std::string getDesc();
	void initConsumable(std::string name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					std::string desc, EdibleEffectType effect, int much);
	
	~CConsumable();
	int getClassType ();

	virtual void read(FILE* pFile);


private:
	std::string m_strDesc;		//���~�y�z
	EdibleEffectType m_effect;	//�ĪG����
	int m_iMuch;				//�v�T�ƭ�
};


#endif