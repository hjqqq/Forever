#ifndef _CBACKPACK_H_
#define _CBACKPACK_H_

#include "CItemTable.h"
#include "Common.h"

class CBackPack
{
public:
	void setGrid(int grid, CItemTable& itm);		//�]�w�椤���e�O����(net pack�ϥ�)
	CItemTable* getItem(int grid);					//���o�o�椺�e
	void addItem(int id, int& stack, int& grid);	//�W�[���~ id ���~�s�� stack �ƶq 
													//grid �Ǧ^�̫�����Ӯ�l

	void initBack();								//�w�]����إߦ������~

private:
	CItemTable m_itemBack[BACK_MAX];

};


#endif