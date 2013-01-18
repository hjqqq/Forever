/** This source file is part of Forever
  * Copyright(c) 2012-2013 The DCI's Forever Team
  *
  * @file   Common.h
  * @author Darren Chen (�����a)
  * @email  darren.z32@msa.hinet.net
  * @date   2012/11/27 */
#ifndef _COMMON_H_
#define _COMMON_H_
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// Add by Darren Chen on 2012/12/22 {
#include <list>
#include <map>
#include <set>
#include <time.h>
#include <math.h>
// } Add by Darren Chen on 2012/12/22

struct BasicAttribute
{
	int iSTR;	//�O�q
	int iVIT;	//��O
	int iDEX;	//�R��
	int iAGI;	//�ӱ�
	int iINT;	//���O
	int iWIL;	//�N��
};

//�i���ݩ�
struct AdvancedAttribute	
{ 
	int iHP;	         //�ͩR�O
	int iMP;	         //�믫�O
	int iHPMax;	      //�̤j�ͩR�O
	int iMPMax;	      //�̤j�믫�O
	int iATK;	      //���z�����O
	int iDEF;	      //���z���m�O
	int iHIT;	      //���z�R���v
	int iCRI;	      //���z�����v
	int iMATK;	      //�]�k�����O
	int iMDEF;	      //�]�k���m�O
	int iMHIT;	      //�]�k�R���v
	int iMCRI;	      //�]�k�����v
	int iSDEF;	      //�޵P���m�O
	int iWDEF;	      //�Z�����m�O
	int iFlee;	      //�j�ײv
	float fMove;      //���ʳt�� �w�]�� 6.0
	float fATKSpeed;  //�����t�� �����ʧ@�H����� 1�U 1.5 �� �w�]�� 1.5
	float fCasting;   //�I�i�t�� �H����� 1.0 �� �w�]�� 1.0
	
};

struct ObscureAttribute
{
	int iHPR;			//�ͩR�^�_�q
	int iMPR;			//�믫�^�_�q
};

//�˳Ƽ�
enum EquipSlot	
{
	MAIN_HAND,	//�D��
	OFF_HAND,	//�Ƥ�
	CHEST,		//�W��
	BELT,		   //�y�a
	LEGS,		   //�Ǥl
	SHOULDER,	//�@��
	GLOVE,		//��M
	BOOT,		   //�c�l
};

enum ItemClassType
{
	WEAPON,
	ARMOR,
	CONSUMABLE,
};

//���~����
enum ItemType	
{
	DAGGER,		//�P��
	SWORD,		//���C
	MACE,		   //�v��
	STAVE,		//�k��
	SPELLBOOK,	//�k��
	ORB,		   //�k�]
	GREATSWORD,	//���C
	POLEARM,	   //�Դu
	BOW,		   //�}
	CLOTH,		//���T
	LEATHER,	   //�֥�
	CHAIN,		//���
	PLATE,		//���ݥ�
	SHIELDS,	   //�޵P
	POTION,		//�Ĥ�
	FOOD,		   //����
	SCROLL,		//���b
	ITEM_TYPE_TOTAL,	//�`��
};

//�˳ƫ~��
enum EquipQuality	
{
	COMMON,	//���q
	RARE,	   //�}��
	LEGEND,	//�ǩ�
	UNIQUE,	//�W�S
	EPIC	//�^��
};

//����Z��/����
enum WeaponWieldType	
{
	ONE_HAND,	//�D��
	TWO_HAND	   //�Ƥ�
};

//�˳Ʀ�m
enum ArmorWearType	
{
	CLOTHES,	   //��A
	BELTS,		//�y�a
	PANTS,		//�Ǥl
	PAULDRONS,	//�@��
	GLOVES,		//��M
	BOOTS		   //�c�l
};

struct AdvancedItem
{
	std::string name;	//�W��
	std::string iconName;//�ϥܦW��
	ItemType type;		//����
	bool soulBind;		//�j�w
	char level;			//����
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

enum MonsterType
{
    MONSTER_ACTIVE,     //�D��
    MONSTER_PASSIVE,    //�Q��
};

enum MonsterGrade
{
    REGULAR_GRADE, //���q
    ELITE_GRADE,  //�׭^
    HERO_GRADE,   //�^��
    LEGEND_GRADE, //�ǻ�
};

enum MonsterClass
{
    MONSTER,
};

struct AngerValue
{
    long long uid;
    int iHatred;
};

const int BACK_ROW = 9;		//row�� 
const int BACK_COLUMN = 3;	//column��
const int BACK_MAX = BACK_ROW * BACK_COLUMN;	//���
const int longStrSize = 256;
const int UI_HOTKEY_NUM = 10;

// Add by Darren Chen on 2012/12/13 {
/** @brief ���o�ثe�t�Ϊ�����P�ɶ�
  * @return �r�ꫬ�A������P�ɶ�(�榡: "2013/01/01 23:59:59") */
std::string getCurDateTime();

/** @brief ���o�ƹ��y��(Client�Ϯy��)
  * @param [in] hWnd �n���o���ӵ������y��
  * @param [out] cx  �ƹ�X�y��
  * @param [out] cy  �ƹ�Y�y�� */
void getMousePos(HWND hWnd, int &cx, int &cy);

/** @brief ���o�ƹ����ù��y��
  * @param [out] cx �ƹ�X�y��
  * @param [out] cy �ƹ�Y�y�� */
void getMouseScreenPos(int &cx, int &cy);

/** @brief ���o��Ӯy���I�������Z��
  * @param x1 �Ĥ@�Ӯy���IX
  * @param y1 �Ĥ@�Ӯy���IY
  * @param x2 �ĤG�Ӯy���IX
  * @param y2 �ĤG�Ӯy���IY
  * @return ���I�������Z�� */
float getDistance(float x1, float y1, float x2, float y2);

/** @brief ���ʲĤ@�Ӯy���I��m��ĤG�Ӯy���I
  * @param [in/out] x1 �Ĥ@�Ӯy���IX
  * @param [in/out] y1 �Ĥ@�Ӯy���IY
  * @param [in] x2     �ĤG�Ӯy���IX
  * @param [in] y2     �ĤG�Ӯy���IY
  * @param [in] step   �C�����ʪ��Z�� */   
void movePoint(float &x1, float &y1, float x2, float y2, float step);

typedef enum tagSCENE_TYPE {
   SCENE_POETA,     // �i��� (�s���)
   SCENE_INSTANCE   // �ƥ�
} SCENE_TYPE;  // �������A

typedef enum tagACTION_EVENT_TYPE {
   AET_NULL,         // �S���ƥ�
   AET_REACH,        // ��F�ؼ��I   (�y�еL���)
   AET_NOT_REACH,    // ����F�ؼ��I (�y�Ч�ʤ�)
   AET_KEY,          // �ֱ���
   AET_KEY_WASD,     // WASD����
   AET_CAST_SKILL,   // �I�i�ޯ�
} ACTION_EVENT_TYPE;  // �ʧ@�ƥ����
// } Add by Darren Chen on 2012/12/13

#endif  // #ifndef _COMMON_H_