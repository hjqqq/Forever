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
	float fATKSpeed;//�����t�� �����ʧ@�H������� 1�U 1.5 �� �w�]�� 1.5
	float fCasting;//�I�i�t�� �H������� 1.0 �� �w�]�� 1.0
	
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
	BOOT		//�c�l
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
	SCROLL		//���b
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
	ONE_HAND,	//���
	TWO_HAND	//����
};

enum ArmorWearType	//�˳Ʀ�m
{
	CLOTHES,	//��A
	BELTS,
	PANTS,		//�Ǥl
	PAULDRONS,	//�@��
	GLOVES,		//��M
	BOOTS		//�c�l
};

struct AdvancedItem
{
	std::wstring name;	//�W��
	ItemType type;		//����
	bool soulBind;		//�j�w
	char level;			//����
	int stackLimit;		//���|�W��
	int sellPrice;		//���
	int buyPrice;		//�R��
};

enum EdibleEffectType
{
	HP,					//�ɦ�
	MP,					//���]
	HPMax,				//�W�[�̤j��q
	MPMax,				//�W�[�̤j�]�q
	Skill,				//�ޯ�
};

#endif  //_COMMON_H_