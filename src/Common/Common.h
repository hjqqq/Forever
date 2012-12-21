/** Copyright (c) 2012-2013 Digital Content Institute.
  * All Rights Reserved.
  *
  * @檔案:     Common.h
  * @用途:     共用
  * @開發者: 
  * @更新日期: 2012/11/27 */
#ifndef _COMMON_H_
#define _COMMON_H_
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

struct AdvancedAttribute	//進階屬性
{ 
	int iHP;	//生命力
	int iMP;	//精神力
	int iHPMax;	//最大生命力
	int iMPMax;	//最大精神力
	int iATK;	//物理攻擊力
	int	iDEF;	//物理防禦力
	int iHIT;	//物理命中率
	int iCRI;	//物理暴擊率
	int iMATK;	//魔法攻擊力
	int iMDEF;	//魔法防禦力
	int	iMHIT;	//魔法命中率
	int iMCRI;	//魔法暴擊率
	int iSDEF;	//盾牌防禦力
	int iWDEF;	//武器防禦力
	int iFlee;	//迴避率
	float fMove;//移動速度 預設值 6.0
	float fATKSpeed;//攻擊速度 揮擊動作以秒為單位 1下 1.5 秒 預設值 1.5
	float fCasting;//施展速度 以秒為單位 1.0 秒 預設值 1.0
	
};

enum EquipSlot	//裝備槽
{
	MAIN_HAND,	//主手
	OFF_HAND,	//副手
	CHEST,		//上衣
	BELT,		//腰帶
	LEGS,		//褲子
	SHOULDER,	//護肩
	GLOVE,		//手套
	BOOT		//鞋子
};

enum ItemType	//物品種類
{
	DAGGER,		//匕首
	SWORD,		//長劍
	MACE,		//釘錘
	STAVE,		//法杖
	SPELLBOOK,	//法書
	ORB,		//法珠
	GREATSWORD,	//巨劍
	POLEARM,	//戰戟
	BOW,		//弓
	CLOTH,		//長袍
	LEATHER,	//皮甲
	CHAIN,		//鏈甲
	PLATE,		//金屬甲
	SHIELDS,	//盾牌
	POTION,		//藥水
	FOOD,		//食物
	SCROLL,		//卷軸
	ITEM_TYPE_TOTAL,	//總數
};

enum EquipQuality	//裝備品質
{
	COMMON,	//普通
	RARE,	//稀有
	LEGEND,	//傳說
	UNIQUE,	//獨特
	EPIC	//史詩
};

enum WeaponWieldType	//單持武器/雙持
{
	ONE_HAND,	//單持
	TWO_HAND	//雙持
};

enum ArmorWearType	//裝備位置
{
	CLOTHES,	//衣服
	BELTS,		//腰帶
	PANTS,		//褲子
	PAULDRONS,	//護肩
	GLOVES,		//手套
	BOOTS		//鞋子
};

struct AdvancedItem
{
	std::string name;	//名稱
	ItemType type;		//種類
	bool soulBind;		//綁定
	char level;		//等級
	int stackLimit;		//堆疊上限
	int sellPrice;		//賣價
	int buyPrice;		//買價
};

enum EdibleEffectType
{
	HP,					//補血
	MP,					//補魔
	HP_MAX,	//增加最大血量
	MP_MAX,	//增加最大魔量
	SKILL,	//技能
};


const int BACK_ROW = 8;		//row橫 
const int BACK_COLUMN = 3;	//column直
const int BACK_MAX = 24;	//格數

#endif  //_COMMON_H_