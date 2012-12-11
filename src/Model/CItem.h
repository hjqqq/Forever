#ifndef _CITEM_H_
#define _CITEM_H_

#include "Common.h"





class CItem					//���~
{
public:
	std::wstring getName();	//���o�W�r
	ItemType getItemType();	//���o���ت��~(ItemType����)
	bool getSoulBind();		//���o�O�_�j�w
	char getLevel();		//���o�i�ϥε���
	int getStackLimit();	//���o���|�W��
	int getSellPrice();		//���o���
	int getBuyPrice();		//���o�R��
	bool isWeapon();		//�ˬd�O�_�Z��
	bool isArmor();			//�ˬd�O�_����
	bool isConsumable();	//�ˬd�O�_���Ӫ��~

	virtual void read(FILE* pFile);		//Ū��
	virtual void write(FILE* pFile);	//�s��
	AdvancedItem* getAll();		//�@�����o�Ҧ��ݭn�~�y�����ظ�T, �ϥΧ���ƫ�ۦ�delete

protected:

	void setName(std::wstring name);
	void setItemType(ItemType type);
	void setSoulBind(bool soulBind);
	void setLevel(char level);
	void setStackLimit(int stackLimit);
	void setSellPrice(int sellPrice);
	void setBuyPrice(int buyPrice);

private:
	std::wstring m_strName;	//�W��
	ItemType m_type;		//����
	bool m_bSoulBind;		//�j�w
	char m_level;			//����
	int m_iStackLimit;		//���|�W��
	int m_iSellPrice;		//���
	int m_iBuyPrice;		//�R��
};



#endif