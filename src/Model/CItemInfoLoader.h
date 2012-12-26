#ifndef _CITEMINFOLOADER_H_
#define _CITEMINFOLOADER_H_

#include "Common.h"
#include "CItem.h"

class CItemInfoLoader
{
public:
	CItem* create (int type);
	bool isWeapon(int type);		//�ˬd�O�_�Z��
	bool isArmor(int type);			//�ˬd�O�_����
	bool isConsumable(int type);	//�ˬd�O�_���Ӫ��~

} ;




#endif