#ifndef _CEQUIP_H_
#define _CEQUIP_H_

#include "Common.h"
#include "CItem.h"

class CEquip:public CItem			//�˳Ʃʪ��~
{
public:
	EquipQuality getQuality();			//���o�~��
	AdvancedAttribute getBaseAttr();	//���o�򥻯�O
	AdvancedAttribute getExtendAttr();	//���o�B�~��O
		
	virtual void read(FILE* pFile);

protected:
	void setQuality(EquipQuality quality);
	void setBaseAttr(AdvancedAttribute baseAttr);
	void setExtendAttr(AdvancedAttribute extendAttr);

private:
	EquipQuality m_quality;			//�~��
	AdvancedAttribute m_baseAttr;	//�˳ư򥻯�O
	AdvancedAttribute m_extendAttr;	//�˳��B�~��O
};



#endif