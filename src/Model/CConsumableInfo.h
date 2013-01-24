#ifndef _CCONSUMABLEINFO_H_
#define _CCONSUMABLEINFO_H_
#include "CItemInfo.h"

//�ӧ��ʪ��~
class CConsumableInfo : public CItemInfo	
{
public:
	std::string getDesc();			//���o���~�y�z
	EdibleEffectType getEffect();	//���o���خĪG
	int getMuch();					//���o�v�T�ƭ�
	void initConsumableInfo(std::string name, std::string iconName, ItemType type, bool soulBind,
					char level, int stackLimit, int sellPrice, int buyPrice,
					std::string desc, EdibleEffectType effect, int much);
	
	~CConsumableInfo();
	ItemClassType getClassType ();

	virtual void read(FILE* pFile);
#ifdef _GAMEENGINE_2D_EDITOR_
	virtual void write(FILE* pFile);
#endif //#ifdef _GAMEENGINE_2D_EDITOR_


private:
	std::string m_strDesc;		//���~�y�z
	EdibleEffectType m_effect;	//�ĪG����
	int m_iMuch;				//�v�T�ƭ�
#ifdef _GAMEENGINE_2D_EDITOR_
	friend class ConsumablePage;
#endif //#ifdef _GAMEENGINE_2D_EDITOR_
};

#endif  // #ifndef _CCONSUMABLEINFO_H_