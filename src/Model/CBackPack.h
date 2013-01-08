#ifndef _CBACKPACK_H_
#define _CBACKPACK_H_
#include "Common.h"
#include "CItem.h"

class CBackPack
{
public:
	void setGrid(int grid, CItem& itm);		          //�]�w�椤���e�O����(net pack�ϥ�)
	CItem* getItem(int grid);					          //���o�o�椺�e
    CItemInfo* getItemInfo(int grid);                       //���o�o�椺�e
	void addItem(int id, int& stack, int& grid);	    //�W�[���~ id ���~�s�� stack �ƶq

	void initBack();								          //�w�]����إߦ������~

private:
	CItem m_itemBack[BACK_MAX];
};

#endif