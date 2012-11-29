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
	float fATKSpeed;//�����t�� �����ʧ@�H����� 1�U 1.5 �� �w�]�� 1.5
	float fCasting;//�I�i�t�� �H����� 1.0 �� �w�]�� 1.0
	
};

enum EquipSlot	//�˳Ƽ�
{
	MAIN_HAND,	//�D��
	OFF_HAND,	//�Ƥ�
	CHEST,		//�W��
	LEGS,		//�Ǥl
	SHOULDER,	//�ӥ�
	GLOVES,		//��M
	BOOTS		//�c�l
};



#endif  //_COMMON_H_