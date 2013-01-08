#ifndef _CBUFF_H_
#define _CBUFF_H_

#include "obj_mTable.h"
#include "CBuffInfoLoader.h"

typedef ObjTable<CBuffInfo*, CBuffInfoLoader> BUFF_INFO;

class CBuff:public BUFF_INFO
{
public:
	static void initBuff();   //��l
	float getSurplus(); //���o����ɶ�
	void create(unsigned int id);   //�]�w���Y�@��
	bool afterTime(float timePass); //��s�ɶ�
    CBuff();
    ~CBuff();

private:
	float m_fSurplus;   //����ɶ�
};

#endif