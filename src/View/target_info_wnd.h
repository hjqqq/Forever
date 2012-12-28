#ifndef _TARGET_INFO_WND_H_
#define _TARGET_INFO_WND_H_

#include "window.h"
#include "monster.h"

class Scene ;
class Unit ;
class TargetInfoWnd:public Window
{
public:
//	Monster* pMonster ;
	Scene* pScene ;
	long long targetUID ;

public:
	~TargetInfoWnd () {};

	Unit* getTarget () ;
	void init (Scene*, float tx, float ty) ;

	bool canDrag (int tx, int ty) ;

	void setTarget (long long) ;

	void onCommand (int id) ;

#ifdef _PROJECT_OGRE_3D_	
	void onMove () ;

	void setZOrder (int z) ;
	void onSwitch () ;
#endif
} ;

#endif