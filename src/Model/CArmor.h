#ifndef _CARMOR_H_
#define _CARMOR_H_

#include "CEquip.h"

class CArmor:public CEquip	//����
{
public:
	ArmorWearType getWear();
	void initArmor(std::string name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, ArmorWearType wear);

	~CArmor();
	int getClassType ();

	void read(FILE* pFile);

private:
	ArmorWearType m_wear;	//�˳Ʀ�m
};


#endif