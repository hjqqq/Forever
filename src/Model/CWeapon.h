#ifndef _CWEAPON_H_
#define _CWEAPON_H_

#include "CEquip.h"

class CWeapon:public CEquip		//�Z��
{
public:
	WeaponWieldType getWield();
	void initWeapon(std::wstring name, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					EquipQuality quality, AdvancedAttribute baseAttr,
					AdvancedAttribute extendAttr, WeaponWieldType wield);
	void read(FILE* pFile);
	void write(FILE* pFile);

private:
	WeaponWieldType m_wield;	//�����覡
};



#endif