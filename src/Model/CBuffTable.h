#ifndef _CBUFFTABLE_H_
#define _CBUFFTABLE_H_

#include "obj_mTable.h"
#include "CBuffInfoLoader.h"

typedef ObjTable<CBuff*, CBuffInfoLoader> BUFF_INFO;

class CBuffTable:public BUFF_INFO
{
public:
	static void initCBuffTable();   //��l
	float getSurplus(); //���o����ɶ�
	void create(unsigned int id);   //�]�w���Y�@��
	bool afterTime(float timePass); //��s�ɶ�
	CBuffTable();
	~CBuffTable();

private:
	float m_fSurplus;   //����ɶ�
};

#endif