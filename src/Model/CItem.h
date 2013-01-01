#ifndef _CITEM_H_
#define _CITEM_H_

#include "Common.h"

class CItem					//���~
{
public:
	std::string getName();	//���o�W�r
	std::string geticonName();
	ItemType getItemType();	//���o���ت��~(ItemType����)
	bool getSoulBind();		//���o�O�_�j�w
	char getLevel();		//���o�i�ϥε���
	int getStackLimit();	//���o���|�W��
	int getSellPrice();		//���o���
	int getBuyPrice();		//���o�R��

	virtual ~CItem();
	virtual int getClassType () = 0;		//�^�Ǩ��@��class(�Z���B����B���өʪ��~)

	virtual void read(FILE* pFile);		//Ū��
	AdvancedItem* getAll();		//�@�����o�Ҧ��ݭn�~�y�����ظ�T, �ϥΧ���ƫ�ۦ�delete

protected:

	void setName(std::string name);
    void seticonName(std::string iconName);
	void setItemType(ItemType type);
	void setSoulBind(bool soulBind);
	void setLevel(char level);
	void setStackLimit(int stackLimit);
	void setSellPrice(int sellPrice);
	void setBuyPrice(int buyPrice);

private:
	std::string m_strName;	//�W��
    std::string m_iconName; //�ϥܦW��
	ItemType m_type;		//����
	bool m_bSoulBind;		//�j�w
	char m_level;			//����
	int m_iStackLimit;		//���|�W��
	int m_iSellPrice;		//���
	int m_iBuyPrice;		//�R��
};



#endif