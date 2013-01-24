#ifndef _CEQUIPINFO_H_
#define _CEQUIPINFO_H_
#include "Common.h"
#include "CItemInfo.h"

//�˳Ʃʪ��~��T
class CEquipInfo : public CItemInfo			
{
public:
	EquipQuality getQuality();			//���o�~��
	AdvancedAttribute getBaseAttr();	//���o�򥻯�O
	AdvancedAttribute getExtendAttr();	//���o�B�~��O
	std::string			getMeshName();		//���o�ҫ��W��
		
	virtual void read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	virtual void write(FILE* pFile);
#endif //#ifdef _GAMEENGINE_2D_EDITOR_

protected:
	void setQuality(EquipQuality quality);
	void setBaseAttr(AdvancedAttribute baseAttr);
	void setExtendAttr(AdvancedAttribute extendAttr);
	void setMeshName(std::string mesh);

private:
	EquipQuality m_quality;			//�~��
	AdvancedAttribute m_baseAttr;	//�˳ư򥻯�O
	AdvancedAttribute m_extendAttr;	//�˳��B�~��O
	std::string			m_strMeshName;	//�ҫ��W��
};

#endif  // #ifndef _CEQUIPINFO_H_