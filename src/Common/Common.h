/** Copyright (c) 2012-2013 Digital Content Institute.
  * All Rights Reserved.
  *
  * @�ɮ�:     Common.h
  * @�γ~:     �@��
  * @�}�o��: 
  * @��s���: 2012/11/27 */
#ifndef _COMMON_H_
#define _COMMON_H_
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

struct BasisAttribute
{
	int iSTR;		//�O�q
	int iVIT;		//��O
	int iDEX;		//�R��
	int iAGI;		//�ӱ�
	int iINT;		//���O
	int iWIL;		//�N��
};

struct AdvancedAttribute	//�i���ݩ�
{ 
	int iHP;	//�ͩR�O
	int iMP;	//�믫�O
	int iHPMax;	//�̤j�ͩR�O
	int iMPMax;	//�̤j�믫�O
	int iATK;	//���z�����O
	int	iDEF;	//���z���m�O
	int iHIT;	//���z�R���v
	int iCRI;	//���z�����v
	int iMATK;	//�]�k�����O
	int iMDEF;	//�]�k���m�O
	int	iMHIT;	//�]�k�R���v
	int iMCRI;	//�]�k�����v
	int iSDEF;	//�޵P���m�O
	int iWDEF;	//�Z�����m�O
	int iFlee;	//�j�ײv
	float fMove;//���ʳt�� �w�]�� 6.0
	float fATKSpeed;//�����t�� �����ʧ@�H����� 1�U 1.5 �� �w�]�� 1.5
	float fCasting;//�I�i�t�� �H����� 1.0 �� �w�]�� 1.0
	
};

struct ObscureAttribute
{
	int iHPR;			//�ͩR�^�_�q
	int iMPR;			//�믫�^�_�q
};

enum EquipSlot	//�˳Ƽ�
{
	MAIN_HAND,	//�D��
	OFF_HAND,	//�Ƥ�
	CHEST,		//�W��
	BELT,		//�y�a
	LEGS,		//�Ǥl
	SHOULDER,	//�@��
	GLOVE,		//��M
	BOOT,		//�c�l
};

enum ItemClassType
{
	WEAPON,
	ARMOR,
	CONSUMABLE,

};

enum ItemType	//���~����
{
	DAGGER,		//�P��
	SWORD,		//���C
	MACE,		//�v��
	STAVE,		//�k��
	SPELLBOOK,	//�k��
	ORB,		//�k�]
	GREATSWORD,	//���C
	POLEARM,	//�Դu
	BOW,		//�}
	CLOTH,		//���T
	LEATHER,	//�֥�
	CHAIN,		//���
	PLATE,		//���ݥ�
	SHIELDS,	//�޵P
	POTION,		//�Ĥ�
	FOOD,		//����
	SCROLL,		//���b
	ITEM_TYPE_TOTAL,	//�`��
};

enum EquipQuality	//�˳ƫ~��
{
	COMMON,	//���q
	RARE,	//�}��
	LEGEND,	//�ǻ�
	UNIQUE,	//�W�S
	EPIC	//�v��
};

enum WeaponWieldType	//����Z��/����
{
	ONE_HAND,	//�D��
	TWO_HAND	//�Ƥ�
};

enum ArmorWearType	//�˳Ʀ�m
{
	CLOTHES,	//��A
	BELTS,		//�y�a
	PANTS,		//�Ǥl
	PAULDRONS,	//�@��
	GLOVES,		//��M
	BOOTS		//�c�l
};

struct AdvancedItem
{
	std::string name;	//�W��
	std::string iconName;//�ϥܦW��
	ItemType type;		//����
	bool soulBind;		//�j�w
	char level;		//����
	int stackLimit;		//���|�W��
	int sellPrice;		//���
	int buyPrice;		//�R��
};

enum EdibleEffectType
{
	EDIBLE_HP,		//�ɦ�
	EDIBLE_MP,		//���]
	EDIBLE_HP_MAX,	//�W�[�̤j��q
	EDIBLE_MP_MAX,	//�W�[�̤j�]�q
	EDIBLE_SKILL,	//�ޯ�
};

enum AttackTarget
{
	ENEMY,				//�Ǫ�
	TEAM,				//�ͤ�
	SELF,				//�ۤv
	GROUND,				//�d��
};

struct ComplexAttribute
{
	AdvancedAttribute AdvAttr;		//�v�T�ݩ�
	ObscureAttribute ObsAttr;
};

struct FloatPrecentAttribute
{
    float fHP;			//�ͩR�O
	float fMP;			//�믫�O
	float fHPMax;			//�̤j�ͩR�O
	float fMPMax;			//�̤j�믫�O
	float fATK;			//���z�����O
	float fDEF;			//���z���m�O
	float fHIT;			//���z�R���v
	float fCRI;			//���z�����v
	float fMATK;			//�]�k�����O
	float fMDEF;			//�]�k���m�O
	float fMHIT;			//�]�k�R���v
	float fMCRI;			//�]�k�����v
	float fSDEF;			//�޵P���m�O
	float fWDEF;			//�Z�����m�O
	float fFlee;			//�j�ײv
	float fMove;		//���ʳt�� �w�]�� 6.0
	float fATKSpeed;	//�����t�� �����ʧ@�H����� 1�U 1.5 �� �w�]�� 1.5
	float fCasting;		//�I�i�t�� �H����� 1.0 �� �w�]�� 1.0
    float fHPR;			//�ͩR�^�_�q
	float fMPR;			//�믫�^�_�q
};

enum tagSKILL_TYPE 
{
	TYPE_ACTIVE,    // �D�ʧޯ�
	TYPE_PASSIVE    // �Q�ʧޯ�
};

enum SkillClassType
{
    SKILL,
};

enum BuffClassType
{
	BUFF,
};

const int BACK_ROW = 8;		//row�� 
const int BACK_COLUMN = 3;	//column��
const int BACK_MAX = 24;	//���

#endif  //_COMMON_H_