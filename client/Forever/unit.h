#ifndef _UNIT_H_
#define _UNIT_H_

#include "windows.h"
#include "Fmath.h"

class Cunit
{
private:

public:
	Cunit() {};
	float x,y,z;
	char LV;
	int HP,MP,MAXHP,MAXMP;
	int STR,VIT,DEX,AGI,WEN,WIL;//INT����r  WEN�N�� ���ݩ�
	float ATK,DEF,HIT,CRI,MOVE,FLEE,
			MATK,MDEF,MHIT,MCRI;//�i���ݩ�

	void draw(HDC hdc);
  
	virtual ~Cunit () {};
};

class Cplayer:public Cunit
{
private:
	float jumpHight;
	char job;

public:
	void move(float,float,float=0);
	void jump();

};

class Cmonster:public Cunit
{
private:

public:

};

#endif